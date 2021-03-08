#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_user_config = std::make_unique<UserConfig>();
    m_playerlist_config = std::make_unique<PlaylistConfig>();
    this->updataPlaylistTable();

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

void MainWindow::updataPlaylistTable()
{
    auto data = m_playerlist_config->data();

    for (auto &playlist_name : data)
    {
        ui->listWidgetPlaylist->addItem(playlist_name.first);
    }
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
    m_search_tracks = m_player->searchTrack(ui->lineEditSearch->text());

    ui->tableWidgetSearch->clearContents();
    ui->tableWidgetSearch->setRowCount(m_search_tracks.size());

    std::size_t row = 0;
    for (auto it_track = m_search_tracks.begin(); it_track != m_search_tracks.end(); ++it_track, ++row)
    {
        ui->tableWidgetSearch->setItem(row, 0, new QTableWidgetItem(it_track->trackParameters().name));
        ui->tableWidgetSearch->setItem(row, 1, new QTableWidgetItem(it_track->trackParameters().artist));
    }
}

void MainWindow::on_actionNewPlaylist_triggered()
{
    bool ok;
    QString name =
        QInputDialog::getText(this, tr("Playlist"), tr("Nomde da Playlist:"), QLineEdit::Normal, tr(""), &ok);

    if (ok && !name.isEmpty())
    {
        ui->listWidgetPlaylist->addItem(name);
        m_playerlist_config->save(name);
    }
}
