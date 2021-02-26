#include "PlaylistWizardDialog.hpp"
#include "ui_PlaylistWizardDialog.h"

PlaylistWizardDialog::PlaylistWizardDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlaylistWizardDialog)
{
    ui->setupUi(this);
}

PlaylistWizardDialog::~PlaylistWizardDialog()
{
    delete ui;
}

void PlaylistWizardDialog::on_pushButtonAdd_clicked()
{
    SearchDialog search_dialog;
    search_dialog.setModal(true);
    search_dialog.exec();
}
