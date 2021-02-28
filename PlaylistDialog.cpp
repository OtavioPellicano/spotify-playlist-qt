#include "PlaylistDialog.hpp"
#include "ui_PlaylistDialog.h"

PlaylistDialog::PlaylistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlaylistDialog)
{
    ui->setupUi(this);
}

PlaylistDialog::~PlaylistDialog()
{
    delete ui;
}

void PlaylistDialog::on_pushButtonNewPlaylist_clicked()
{
    PlaylistWizardDialog playlist_wizard_dialog;
    playlist_wizard_dialog.setModal(true);
    playlist_wizard_dialog.exec();
}

void PlaylistDialog::on_pushButtonEdit_clicked()
{
    // Verify if any preview playlist was selected
    // if so, load the selected playlist
    // otherwise, error
    PlaylistWizardDialog playlist_wizard_dialog;
    playlist_wizard_dialog.setModal(true);
    playlist_wizard_dialog.exec();
}
