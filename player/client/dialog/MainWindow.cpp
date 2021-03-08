#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_user_config = std::make_unique<UserConfig>();
    this->updateConnectPushButton();

    this->setupTable(ui->tableWidgetSearch);
    this->setupTable(ui->tableWidgetTracks);
    this->setEnabledAllGroupBox(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userConfigChanged(const UserConfig &user_config)
{
    m_user_config = std::make_unique<UserConfig>(user_config);
    this->updateConnectPushButton();
}

void MainWindow::on_actionUser_triggered()
{
    m_user_dialog = std::make_unique<UserDialog>(this);
    connect(m_user_dialog.get(), &UserDialog::userConfigChanged, this, &MainWindow::userConfigChanged);
    m_user_dialog->exec();
}

void MainWindow::updateConnectPushButton()
{
    ui->actionConnectAPI->setEnabled(m_user_config->updated());
}

void MainWindow::setupTable(QTableWidget *table)
{
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setEnabledAllGroupBox(bool enabled)
{
    ui->groupBoxPlaylist->setEnabled(enabled);
    ui->groupBoxCurrentSong->setEnabled(enabled);
    ui->groupBoxSearch->setEnabled(enabled);
    ui->groupBoxSongs->setEnabled(enabled);
}

void MainWindow::on_actionConnectAPI_triggered()
{
    if (m_player == nullptr)
    {
        m_player = std::make_unique<Player>(this);
        this->setEnabledAllGroupBox(true);
    }
    else
    {
        if (m_player->isGranted())
        {
            auto msg_box = QMessageBox(this);
            msg_box.setText("Você já está conectado!");
            msg_box.exec();
        }
        else
        {
            m_player = nullptr;
            this->setEnabledAllGroupBox(false);
        }
    }
}

void MainWindow::on_lineEditSearch_returnPressed()
{
    auto tracks = m_player->searchTrack(ui->lineEditSearch->text());

    ui->tableWidgetSearch->clearContents();
    ui->tableWidgetSearch->setRowCount(tracks.size());

    std::size_t row = 0;
    for (auto it_track = tracks.begin(); it_track != tracks.end(); ++it_track, ++row)
    {
        ui->tableWidgetSearch->setItem(row, 0, new QTableWidgetItem(it_track->trackParameters().name));
        ui->tableWidgetSearch->setItem(row, 1, new QTableWidgetItem(it_track->trackParameters().artist));
    }
}
