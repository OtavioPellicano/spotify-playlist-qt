#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
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
    void userConfigChanged(const UserConfig &user_config);

  private slots:
    void on_actionUser_triggered();

    void on_actionConnectAPI_triggered();

    void on_lineEditSearch_returnPressed();

  private:
    void updateConnectPushButton();

    void setupTable(QTableWidget *table);
    void setEnabledAllGroupBox(bool enabled);

  private:
    Ui::MainWindow *ui;
    std::unique_ptr<UserDialog> m_user_dialog;
    std::unique_ptr<UserConfig> m_user_config;
    std::unique_ptr<Player> m_player;
};

#endif // MAINWINDOW_H
