#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSearch_triggered()
{
    SearchDialog search_dialog;
    search_dialog.setModal(true);
    search_dialog.exec();
}

void MainWindow::on_actionPlaylist_triggered()
{
    PlaylistDialog playlist_dialog;
    playlist_dialog.setModal(true);
    playlist_dialog.exec();
}
