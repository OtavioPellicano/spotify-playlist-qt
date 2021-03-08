#include "Player.hpp"

Player::Player(QObject *parent)
    : Spotify(parent)
{
}

QVector<Track> Player::search_track(const QString &criteria)
{
    this->set_tracks(Spotify::search_track(criteria));

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
