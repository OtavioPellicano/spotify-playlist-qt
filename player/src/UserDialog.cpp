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
    ui->lineEditClientID->setText(QString::fromStdString(user_data.client_id));
    ui->lineEditClientSecret->setText(QString::fromStdString(user_data.client_secret));
}

void UserDialog::on_pushButtonOk_clicked()
{
    auto client_id = ui->lineEditClientID->text().toStdString();
    auto client_secret = ui->lineEditClientSecret->text().toStdString();

    if (client_id.empty() || client_secret.empty())
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
