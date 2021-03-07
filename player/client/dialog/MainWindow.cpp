#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_user_config = std::make_unique<UserConfig>();
    this->update_connect_push_button();
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

void MainWindow::on_actionPlaylist_triggered()
{
    m_playlist_dialog = std::make_unique<PlaylistDialog>(this);
    m_playlist_dialog->exec();
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

void MainWindow::on_actionConnectAPI_triggered()
{
    if (m_spotify == nullptr)
    {
        m_spotify = std::make_unique<Spotify>(this, *m_user_config.get());
    }
    else
    {
        auto msg_box = QMessageBox(this);
        msg_box.setText("Você já está conectado!");
        msg_box.exec();
    }
}
