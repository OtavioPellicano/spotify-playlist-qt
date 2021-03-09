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
        m_updated = false;
        file.close();
    }
}

bool PlaylistConfig::updated() const
{
    return m_updated;
}

const PlaylistData &PlaylistConfig::data()
{
    if (!m_updated)
    {
        this->update();
    }

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
        m_updated = true;
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

    m_playlist_data[{playlist_name, track_param.id}] = track_param;
}

void PlaylistConfig::removePlaylist(const QString &playlist_name)
{
    this->update();

    for (auto i = m_playlist_data.begin(), last = m_playlist_data.end(); i != last;)
    {
        // TODO implement Predicate
        if (playlist_name == i->first.first)
        {
            i = m_playlist_data.erase(i);
        }
        else
        {
            ++i;
        }
    }

    this->savePlaylistData(m_playlist_data);
}

void PlaylistConfig::removeTrackFromPlaylist(const QString &playlist_name, const QString &track_id)
{
    this->update();
    auto key = std::pair<QString, QString>{playlist_name, track_id};

    for (auto i = m_playlist_data.begin(), last = m_playlist_data.end(); i != last;)
    {
        // TODO implement Predicate
        if (key == i->first)
        {
            i = m_playlist_data.erase(i);
        }
        else
        {
            ++i;
        }
    }

    this->savePlaylistData(m_playlist_data);
}
