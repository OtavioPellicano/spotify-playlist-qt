#include "UserDialog.hpp"
#include "ui_UserDialog.h"

UserDialog::UserDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserDialog)
{
    ui->setupUi(this);

    ui->lineEditClientID->setPlaceholderText("Client ID");
    ui->lineEditClientSecret->setPlaceholderText("Client Secret");

    this->update_gui();
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::update_gui()
{
    auto user_data = m_user_config.user_data();
    ui->lineEditClientID->setText(user_data.client_id);
    ui->lineEditClientSecret->setText(user_data.client_secret);
}

void UserDialog::on_pushButtonOk_clicked()
{
    auto client_id = ui->lineEditClientID->text();
    auto client_secret = ui->lineEditClientSecret->text();

    if (client_id.isEmpty() || client_secret.isEmpty())
    {
        QMessageBox msg(this);
        msg.setText("Atualize os dois campos");
        msg.exec();
    }
    else
    {
        m_user_config.save_user_data(client_id, client_secret);
        m_user_config.update();
        emit this->user_config_changed(m_user_config);
        this->accept();
    }
}
