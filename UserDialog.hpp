#ifndef USERDIALOG_HPP
#define USERDIALOG_HPP

#include <QDialog>

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();

  private:
    Ui::UserDialog *ui;
};

#endif // USERDIALOG_HPP
