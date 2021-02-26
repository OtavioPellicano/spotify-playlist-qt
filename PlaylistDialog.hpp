#ifndef PLAYLISTDIALOG_HPP
#define PLAYLISTDIALOG_HPP

#include "PlaylistWizardDialog.hpp"
#include <QDialog>

namespace Ui
{
class PlaylistDialog;
}

class PlaylistDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit PlaylistDialog(QWidget *parent = nullptr);
    ~PlaylistDialog();

  private slots:
    void on_pushButtonNewPlaylist_clicked();

    void on_pushButtonEdit_clicked();

  private:
    Ui::PlaylistDialog *ui;
};

#endif // PLAYLISTDIALOG_HPP
