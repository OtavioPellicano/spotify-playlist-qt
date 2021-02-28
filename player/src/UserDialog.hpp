#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "UserConfig.hpp"

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

  private:
    void update_gui();

  private:
    Ui::UserDialog *ui;
    UserConfig m_user_config;
};

#endif // USERDIALOG_H
