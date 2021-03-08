#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "Spotify.hpp"
#include "Track.hpp"

class Player : public Spotify
{
  public:
    explicit Player(QObject *parent = nullptr);
    QVector<Track> search_track(const QString &criteria);

  private:
    void set_tracks(const QJsonObject &json);

    QVector<Track> m_tracks;
};

#endif // PLAYER_HPP
