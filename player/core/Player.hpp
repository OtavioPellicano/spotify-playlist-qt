#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "PlaylistConfig.hpp"
#include "Spotify.hpp"
#include "Track.hpp"
#include "UserConfig.hpp"

class Player : public Spotify
{
  public:
    explicit Player(QObject *parent = nullptr);
    QVector<Track> searchTrack(const QString &criteria, int limit = 10);

    const QVector<Track> &tracksBySearch() const;

    UserConfig userConfig();

    void setUserData(const UserData &user_data);

    PlaylistConfig playlistConfig() const;

  private:
    void setTracks(const QJsonObject &json);

  private:
    QVector<Track> m_search_tracks;
    UserConfig m_user_config;
    PlaylistConfig m_playlist_config;
};

#endif // PLAYER_HPP
