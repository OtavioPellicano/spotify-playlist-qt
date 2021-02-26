#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "PlaylistDialog.hpp"
#include "SearchDialog.hpp"

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

  private slots:
    void on_actionSearch_triggered();

    void on_actionPlaylist_triggered();

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
