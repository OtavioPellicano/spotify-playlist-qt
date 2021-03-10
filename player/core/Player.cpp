#include "Player.hpp"

Player::Player(QObject *parent)
    : Spotify(parent)
{
}

QVector<Track> Player::searchTrack(const QString &criteria, int limit)
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

const QVector<Track> &Player::tracksBySearch() const
{
    return m_search_tracks;
}
