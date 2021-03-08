#include "PlaylistConfig.hpp"

PlaylistConfig::PlaylistConfig()
{
    this->update();
}

void PlaylistConfig::save(PlaylistData &playlist_data)
{
    this->update();
    if (auto file = std::ofstream(m_file_name))
    {
        this->save_playlist_data(file, m_playlist_data);
        this->save_playlist_data(file, playlist_data);
        m_updated = false;
        file.close();
    }
}

void PlaylistConfig::save(const QString &playlist_name)
{
    PlaylistData playlist_data;
    playlist_data[playlist_name][""] = TrackParameters();
    this->save(playlist_data);
}

void PlaylistConfig::save_playlist_data(std::ofstream &file, PlaylistData playlist_data)
{
    auto sep = QString(",");
    for (auto it_play = playlist_data.begin(); it_play != playlist_data.end(); ++it_play)
    {
        for (auto it_id = it_play->second.begin(); it_id != it_play->second.end(); ++it_id)
        {
            auto res = QStringList{it_play->first, it_id->first, it_id->second.toString(sep)}.join(sep);
            file << res.toStdString() << std::endl;
        }
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
            this->updatePlaylistData(QString::fromStdString(str).split(","));
        }

        file.close();
        m_updated = true;
    }
}

void PlaylistConfig::updatePlaylistData(const QStringList &str_csv)
{
    TrackParameters track_param;
    auto &playlist_name = str_csv[0];
    track_param.name = str_csv[1];
    track_param.id = str_csv[2];
    track_param.album = str_csv[3];
    track_param.album_id = str_csv[4];
    track_param.artist = str_csv[5];
    track_param.artist_id = str_csv[6];
    track_param.duration = str_csv[7].toInt();

    m_playlist_data[playlist_name][track_param.id] = track_param;
}
