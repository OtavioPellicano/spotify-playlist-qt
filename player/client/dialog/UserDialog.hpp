#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "core/UserConfig.hpp"

namespace Ui
{
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();

  private slots:
    void on_pushButtonOk_clicked();

  signals:
    void userConfigChanged(const UserData &user_data);

  private:
    void updateGui();

  private:
    Ui::UserDialog *ui;
    UserConfig m_user_config;
};

#endif // USERDIALOG_H
