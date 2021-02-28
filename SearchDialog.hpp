#ifndef SEARCHDIALOG_HPP
#define SEARCHDIALOG_HPP

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

  private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_HPP
