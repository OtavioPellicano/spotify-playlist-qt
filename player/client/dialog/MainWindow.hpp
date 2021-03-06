#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <memory>

#include "PlaylistDialog.hpp"
#include "UserDialog.hpp"
#include "core/Spotify.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void on_user_config_changed(const UserConfig &user_config);

  private slots:
    void on_actionPlaylist_triggered();
    void on_actionUser_triggered();

    void on_actionConnectAPI_triggered();

  private:
    void update_connect_push_button();

  private:
    Ui::MainWindow *ui;
    std::unique_ptr<UserDialog> m_user_dialog;
    std::unique_ptr<PlaylistDialog> m_playlist_dialog;
    std::unique_ptr<UserConfig> m_user_config;
    std::unique_ptr<Spotify> m_spotify;
};

#endif // MAINWINDOW_H
