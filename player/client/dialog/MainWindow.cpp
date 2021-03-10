#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_player = std::make_unique<Player>(this);
    m_user_dialog = std::make_unique<UserDialog>(this);

    this->setupTable(ui->tableWidgetSearch);
    this->setupTable(ui->tableWidgetTracks);
    this->setEnabledAllGroupBox(false);

    connect(m_player.get(), &Player::granted, this, &MainWindow::on_granted);
    connect(m_user_dialog.get(), &UserDialog::userConfigChanged, this, &MainWindow::userConfigChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userConfigChanged(const UserData &user_data)
{
    m_player->userConfig().setUserData(user_data);
}

void MainWindow::on_actionUser_triggered()
{
    m_user_dialog->exec();
}

void MainWindow::setupTable(QTableWidget *table)
{
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setEnabledAllGroupBox(bool enabled)
{
    ui->groupBoxPlaylist->setEnabled(enabled);
    ui->groupBoxCurrentSong->setEnabled(enabled);
    ui->groupBoxSearch->setEnabled(enabled);
    ui->groupBoxSongs->setEnabled(enabled);
}

void MainWindow::updataPlaylistList()
{
    ui->listWidgetPlaylist->clear();
    ui->listWidgetPlaylist->addItems(m_player->playlistNames());
}

void MainWindow::addTrackToPlaylist(const QString &playlist_name, const TrackParameters &track_parameters)
{
    PlaylistData playlist_data;
    playlist_data[{playlist_name, track_parameters.id}] = track_parameters;
    m_player->playlistConfig().save(playlist_data);
    this->updataPlaylistList();
}

void MainWindow::addTrackToPlaylist(const QString &playlist_name)
{
    this->addTrackToPlaylist(playlist_name, TrackParameters());
}

void MainWindow::updateTrackTable(const QString &playlist_name)
{
    auto tracks = this->m_player->updatePlaylistTracks(playlist_name);

    this->updateTable(ui->tableWidgetTracks, tracks);
}

void MainWindow::updateTable(QTableWidget *table, const QVector<Track> &tracks)
{
    table->clearContents();
    table->setRowCount(tracks.size());

    std::size_t row = 0;
    for (auto it_track = tracks.begin(); it_track != tracks.end(); ++it_track, ++row)
    {
        table->setItem(row, 0, new QTableWidgetItem(it_track->trackParameters().name));
        table->setItem(row, 1, new QTableWidgetItem(it_track->trackParameters().artist));
        table->setItem(row, 2, new QTableWidgetItem(it_track->trackParameters().album));
        table->setItem(
            row, 3,
            new QTableWidgetItem(
                QDateTime::fromTime_t(it_track->trackParameters().duration / 1000).toUTC().toString("mm:ss")));
    }
}

void MainWindow::on_actionConnectAPI_triggered()
{
    m_player->connectToAPI();
}

void MainWindow::on_lineEditSearch_returnPressed()
{
    ui->lineEditSearch->setEnabled(false);
    m_player->searchTrack(ui->lineEditSearch->text());

    this->updateTable(ui->tableWidgetSearch, m_player->tracksBySearch());

    ui->lineEditSearch->setEnabled(true);
}

void MainWindow::on_tableWidgetSearch_cellDoubleClicked(int row, int /*column*/)
{
    qDebug() << ui->listWidgetPlaylist->currentRow();

    QMessageBox msgbox(this);
    if (ui->listWidgetPlaylist->currentRow() > -1)
    {
        const auto &tracks_by_search = m_player->tracksBySearch();
        QString playlist_name = ui->listWidgetPlaylist->currentItem()->text();
        qDebug() << tracks_by_search[row].trackParameters().toString();
        auto playlist_row = ui->listWidgetPlaylist->currentRow();
        this->addTrackToPlaylist(playlist_name, tracks_by_search[row].trackParameters());
        ui->listWidgetPlaylist->setCurrentRow(playlist_row);
        this->updateTrackTable(playlist_name);
    }
    else
    {
        msgbox.setText("Escolha uma playlist para adicionar a música");
        msgbox.exec();
    }
}

void MainWindow::on_listWidgetPlaylist_itemClicked(QListWidgetItem *item)
{
    this->updateTrackTable(item->text());
}

void MainWindow::on_listWidgetPlaylist_itemDoubleClicked(QListWidgetItem *item)
{
    QString playlist_name = item->text();
    QMessageBox msg_box(this);
    msg_box.setText(QString("Remover \"%1\" da playlist?").arg(playlist_name));
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setButtonText(QMessageBox::Yes, "Sim");
    msg_box.setButtonText(QMessageBox::No, "Não");

    if (msg_box.exec() == QMessageBox::Yes)
    {
        m_player->playlistConfig().removePlaylist(item->text());
        this->updataPlaylistList();
        ui->tableWidgetTracks->clearContents();
        ui->tableWidgetTracks->setRowCount(0);
    }
}

void MainWindow::on_pushButtonNewPlaylist_clicked()
{
    bool ok;
    QString name =
        QInputDialog::getText(this, tr("Playlist"), tr("Nomde da Playlist:"), QLineEdit::Normal, tr(""), &ok);

    if (ok && !name.isEmpty())
    {
        this->addTrackToPlaylist(name);
    }
}

void MainWindow::on_tableWidgetTracks_itemDoubleClicked(QTableWidgetItem *item)
{
    QString playlist_name = ui->listWidgetPlaylist->currentItem()->text();
    QString track_name = item->text();
    QMessageBox msg_box(this);
    msg_box.setText(QString("Remover \"%1\" de \"%2\"?").arg(track_name).arg(playlist_name));
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setButtonText(QMessageBox::Yes, "Sim");
    msg_box.setButtonText(QMessageBox::No, "Não");

    if (msg_box.exec() == QMessageBox::Yes)
    {
        auto track = m_player->playlistTracks()[item->row()];
        m_player->playlistConfig().removeTrackFromPlaylist(playlist_name, track.trackParameters().id);
        this->updateTrackTable(playlist_name);
    }
}

void MainWindow::on_granted()
{
    this->setEnabledAllGroupBox(true);
    this->updataPlaylistList();
}

void MainWindow::on_pushButtonPlay_clicked()
{
    if (ui->tableWidgetTracks->rowCount())
    {
        auto track_row = ui->tableWidgetTracks->currentRow() > -1 ? ui->tableWidgetTracks->currentRow() : 0;

        auto current_track = m_player->playlistTracks()[track_row];
        m_player->playTrack(current_track);

        ui->tableWidgetTracks->setCurrentCell(track_row, 0);
    }
}
