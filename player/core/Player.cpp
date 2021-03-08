#include "Player.hpp"

Player::Player(QObject *parent)
    : Spotify(parent)
{
}

QVector<Track> Player::search_track(const QString &criteria, int limit)
{
    this->set_tracks(Spotify::search_track(criteria, limit));

    return m_tracks;
}

void Player::set_tracks(const QJsonObject &json)
{
    m_tracks.clear();
    m_tracks.reserve(json["tracks"].toObject()["total"].toInt());
    foreach (auto track, json["tracks"].toObject()["items"].toArray())
    {
        m_tracks.append(Track(track.toObject()));
    }
}
