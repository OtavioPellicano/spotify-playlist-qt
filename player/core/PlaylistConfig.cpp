#include "PlaylistConfig.hpp"

PlaylistConfig::PlaylistConfig()
{
    this->update();
}

void PlaylistConfig::save(PlaylistData &playlist_data)
{
    this->update();
    m_playlist_data.merge(playlist_data);
    this->savePlaylistData(m_playlist_data);
}

void PlaylistConfig::savePlaylistData(PlaylistData &playlist_data)
{

    if (auto file = std::ofstream(m_file_name))
    {
        for (auto it_play = playlist_data.begin(); it_play != playlist_data.end(); ++it_play)
        {
            auto res =
                QStringList{it_play->first.first, it_play->first.second, it_play->second.toString(m_sep)}.join(m_sep);
            file << res.toStdString() << std::endl;
        }
        file.close();
    }
}

const PlaylistData &PlaylistConfig::data()
{
    this->update();

    return m_playlist_data;
}

void PlaylistConfig::update()
{
    if (auto file = std::ifstream(m_file_name))
    {
        m_playlist_data.clear();
        std::string str;
        while (std::getline(file, str))
        {
            this->updatePlaylistData(QString::fromStdString(str).split(m_sep));
        }

        file.close();
    }
}

void PlaylistConfig::updatePlaylistData(const QStringList &str_csv)
{
    TrackParameters track_param;
    auto &playlist_name = str_csv[0];
    track_param.name = str_csv[2];
    track_param.id = str_csv[3];
    track_param.album = str_csv[4];
    track_param.album_id = str_csv[5];
    track_param.artist = str_csv[6];
    track_param.artist_id = str_csv[7];
    track_param.duration = str_csv[8].toInt();
    track_param.uri = str_csv[9];

    m_playlist_data[{playlist_name, track_param.id}] = track_param;
}

void PlaylistConfig::removePlaylist(const QString &playlist_name)
{
    auto playlist_equals = [](const Key &key_1, const Key &key_2) -> bool { return key_1.first == key_2.first; };
    this->remover(m_playlist_data, Key{playlist_name, ""}, playlist_equals);
}

void PlaylistConfig::removeTrackFromPlaylist(const QString &playlist_name, const QString &track_id)
{
    auto key_equals = [](const Key &key_1, const Key &key_2) -> bool { return key_1 == key_2; };
    this->remover(m_playlist_data, Key{playlist_name, track_id}, key_equals);
}

void PlaylistConfig::eraseIf(
    PlaylistData &playlist_data, const Key &key, std::function<bool(const Key &, const Key &)> predicate)
{
    for (auto i = playlist_data.begin(), last = playlist_data.end(); i != last;)
    {
        if (predicate(i->first, key))
        {
            i = playlist_data.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

void PlaylistConfig::remover(
    PlaylistData &playlist_data, const Key &key, std::function<bool(const Key &, const Key &)> predicate)
{
    this->update();
    this->eraseIf(playlist_data, key, predicate);

    this->savePlaylistData(playlist_data);
}
