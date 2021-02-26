#ifndef PLAYLISTWIZARDDIALOG_HPP
#define PLAYLISTWIZARDDIALOG_HPP

#include <QDialog>

#include "SearchDialog.hpp"

namespace Ui
{
class PlaylistWizardDialog;
}

class PlaylistWizardDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit PlaylistWizardDialog(QWidget *parent = nullptr);
    ~PlaylistWizardDialog();

  private slots:
    void on_pushButtonAdd_clicked();

  private:
    Ui::PlaylistWizardDialog *ui;
};

#endif // PLAYLISTWIZARDDIALOG_HPP
