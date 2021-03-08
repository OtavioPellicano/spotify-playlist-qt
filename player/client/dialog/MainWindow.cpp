#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_user_config = std::make_unique<UserConfig>();
    this->update_connect_push_button();

    this->setup_table(ui->tableWidgetSearch);
    this->setup_table(ui->tableWidgetTracks);
    this->set_enabled_all_group_box(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_user_config_changed(const UserConfig &user_config)
{
    m_user_config = std::make_unique<UserConfig>(user_config);
    this->update_connect_push_button();
}

void MainWindow::on_actionUser_triggered()
{
    m_user_dialog = std::make_unique<UserDialog>(this);
    connect(m_user_dialog.get(), &UserDialog::user_config_changed, this, &MainWindow::on_user_config_changed);
    m_user_dialog->exec();
}

void MainWindow::update_connect_push_button()
{
    ui->actionConnectAPI->setEnabled(m_user_config->updated());
}

void MainWindow::setup_table(QTableWidget *table)
{
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::set_enabled_all_group_box(bool enabled)
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
        this->set_enabled_all_group_box(true);
    }
    else
    {
        if (m_player->is_granted())
        {
            auto msg_box = QMessageBox(this);
            msg_box.setText("Você já está conectado!");
            msg_box.exec();
        }
        else
        {
            m_player = nullptr;
            this->set_enabled_all_group_box(false);
        }
    }
}

void MainWindow::on_lineEditSearch_returnPressed()
{
    auto names = m_player->search_track(ui->lineEditSearch->text());

    ui->tableWidgetSearch->clearContents();

    ui->tableWidgetSearch->setRowCount(names.size());
    std::size_t row = 0;
    for (auto it_list = names.begin(); it_list != names.end(); ++it_list, ++row)
    {
        const auto line_split = it_list->split(",");
        const auto &name = line_split[0];
        const auto &artist = line_split[1];
        ui->tableWidgetSearch->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableWidgetSearch->setItem(row, 1, new QTableWidgetItem(artist));
    }
}
