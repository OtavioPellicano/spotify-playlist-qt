#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "Spotify.hpp"
#include "Track.hpp"

class Player : public Spotify
{
  public:
    explicit Player(QObject *parent = nullptr);
    QVector<Track> searchTrack(const QString &criteria, int limit = 10);

  private:
    void setTracks(const QJsonObject &json);

    QVector<Track> m_tracks;
};

#endif // PLAYER_HPP
