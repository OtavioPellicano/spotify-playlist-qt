#include "PlaylistDialog.hpp"
#include "ui_PlaylistDialog.h"

PlaylistDialog::PlaylistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaylistDialog)
{
    ui->setupUi(this);
}

PlaylistDialog::~PlaylistDialog()
{
    delete ui;
}
