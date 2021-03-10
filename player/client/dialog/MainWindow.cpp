#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_player = std::make_unique<Player>(this);
    m_user_dialog = std::make_unique<UserDialog>(this);
    this->updataPlaylistTable();

    this->setupTable(ui->tableWidgetSearch);
    this->setupTable(ui->tableWidgetTracks);
    this->setEnabledAllGroupBox(false);

    connect(m_player.get(), &Player::granted, this, &MainWindow::setEnabledAllGroupBox);
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

void MainWindow::updataPlaylistTable()
{
    auto data = m_player->playlistConfig().data();

    m_playlist_names.clear();
    for (auto &playlist_name : data)
    {
        m_playlist_names.insert(playlist_name.first.first);
    }
    ui->listWidgetPlaylist->clear();
    ui->listWidgetPlaylist->addItems(m_playlist_names.values());
}

void MainWindow::addTrackToPlaylist(const QString &playlist_name, const TrackParameters &track_parameters)
{
    PlaylistData playlist_data;
    playlist_data[{playlist_name, track_parameters.id}] = track_parameters;
    m_player->playlistConfig().save(playlist_data);
    this->updataPlaylistTable();
}

void MainWindow::addTrackToPlaylist(const QString &playlist_name)
{
    this->addTrackToPlaylist(playlist_name, TrackParameters());
}

void MainWindow::updateTrackTable(const QString &playlist_name)
{
    auto data = m_player->playlistConfig().data();
    QVector<QStringList> tracks;
    m_playlist_tracks.clear();
    for (auto &item : data)
    {
        if (!item.first.second.isEmpty() && item.first.first == playlist_name)
        {
            auto &param = item.second;
            m_playlist_tracks.append(param);
            tracks.append(QStringList(
                {param.name, param.artist, param.album,
                 QDateTime::fromTime_t(param.duration / 1000).toUTC().toString("mm:ss")}));
        }
    }

    ui->tableWidgetTracks->clearContents();
    ui->tableWidgetTracks->setRowCount(tracks.size());

    for (int i = 0; i < tracks.size(); ++i)
    {
        auto item = tracks[i];
        ui->tableWidgetTracks->setItem(i, 0, new QTableWidgetItem(item[0]));
        ui->tableWidgetTracks->setItem(i, 1, new QTableWidgetItem(item[1]));
        ui->tableWidgetTracks->setItem(i, 2, new QTableWidgetItem(item[2]));
        ui->tableWidgetTracks->setItem(i, 3, new QTableWidgetItem(item[3]));
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

    const auto &tracks_by_search = m_player->tracksBySearch();

    ui->tableWidgetSearch->clearContents();
    ui->tableWidgetSearch->setRowCount(tracks_by_search.size());

    std::size_t row = 0;
    for (auto it_track = tracks_by_search.begin(); it_track != tracks_by_search.end(); ++it_track, ++row)
    {
        ui->tableWidgetSearch->setItem(row, 0, new QTableWidgetItem(it_track->trackParameters().name));
        ui->tableWidgetSearch->setItem(row, 1, new QTableWidgetItem(it_track->trackParameters().artist));
        ui->tableWidgetSearch->setItem(row, 2, new QTableWidgetItem(it_track->trackParameters().album));
        ui->tableWidgetSearch->setItem(
            row, 3,
            new QTableWidgetItem(
                QDateTime::fromTime_t(it_track->trackParameters().duration / 1000).toUTC().toString("mm:ss")));
    }

    ui->lineEditSearch->setEnabled(true);
}

void MainWindow::on_tableWidgetSearch_cellDoubleClicked(int row, int /*column*/)
{
    qDebug() << ui->listWidgetPlaylist->currentRow();

    QMessageBox msgbox;
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
        this->updataPlaylistTable();
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
        auto track = m_playlist_tracks[item->row()];
        m_player->playlistConfig().removeTrackFromPlaylist(playlist_name, track.id);
        this->updateTrackTable(playlist_name);
    }
}
