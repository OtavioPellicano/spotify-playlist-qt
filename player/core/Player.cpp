#include "Player.hpp"

Player::Player(QObject *parent)
    : Spotify(parent)
{
}

const QVector<Track> &Player::searchTrack(const QString &criteria, int limit)
{
    this->setTracks(Spotify::searchTrack(criteria, limit));

    return m_search_tracks;
}

void Player::setTracks(const QJsonObject &json)
{
    m_search_tracks.clear();
    m_search_tracks.reserve(json["tracks"].toObject()["total"].toInt());
    foreach (auto track, json["tracks"].toObject()["items"].toArray())
    {
        m_search_tracks.append(Track(track.toObject()));
    }
}

const QVector<Track> &Player::playlistTracks() const
{
    return m_playlist_tracks;
}

QVector<Track> Player::updatePlaylistTracks(const QString playlist_name)
{
    auto data = this->playlistConfig().data();
    QVector<Track> tracks;
    m_playlist_tracks.clear();
    for (auto &item : data)
    {
        if (!item.first.second.isEmpty() && item.first.first == playlist_name)
        {
            auto &param = item.second;
            m_playlist_tracks.append(param);
            tracks.append(item.second);
        }
    }

    return tracks;
}

void Player::playTrack(const Track &track)
{
    qDebug() << "Playing... " << track.trackParameters().name;
    this->playTrack(track.trackParameters().uri);
}

const QStringList &Player::playlistNames()
{
    QSet<QString> playlist_names;
    auto data = this->playlistConfig().data();

    playlist_names.clear();
    for (auto &playlist_name : data)
    {
        playlist_names.insert(playlist_name.first.first);
    }

    m_playlist_names = playlist_names.values();
    m_playlist_names.sort(Qt::CaseInsensitive);

    return m_playlist_names;
}

PlaylistConfig Player::playlistConfig() const
{
    return m_playlist_config;
}

void Player::setUserData(const UserData &user_data)
{
    m_user_config.setUserData(user_data);
}

UserConfig &Player::userConfig()
{
    return m_user_config;
}

const QVector<Track> &Player::tracksBySearch() const
{
    return m_search_tracks;
}
