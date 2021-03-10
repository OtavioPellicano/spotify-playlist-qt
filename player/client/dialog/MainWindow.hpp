#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QDebug>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QSet>
#include <QTableWidget>
#include <memory>

#include "UserDialog.hpp"
#include "core/Player.hpp"

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
    void userConfigChanged(const UserData &user_data);

  private slots:
    void on_actionUser_triggered();

    void on_actionConnectAPI_triggered();

    void on_lineEditSearch_returnPressed();

    void on_tableWidgetSearch_cellDoubleClicked(int row, int column);

    void on_listWidgetPlaylist_itemClicked(QListWidgetItem *item);

    void on_listWidgetPlaylist_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButtonNewPlaylist_clicked();

    void on_tableWidgetTracks_itemDoubleClicked(QTableWidgetItem *item);

    void on_granted();

    void on_pushButtonPlay_clicked();

  private:
    void setEnabledAllGroupBox(bool enabled);
    void setupTable(QTableWidget *table);
    void updataPlaylistList();
    void addTrackToPlaylist(const QString &playlist_name, const TrackParameters &track_parameters);
    void addTrackToPlaylist(const QString &playlist_name);
    void updateTrackTable(const QString &playlist_name);
    void updateTable(QTableWidget *table, const QVector<Track> &tracks);

  private:
    Ui::MainWindow *ui;
    std::unique_ptr<UserDialog> m_user_dialog;
    std::unique_ptr<Player> m_player;
};

#endif // MAINWINDOW_H
