#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "PlaylistConfig.hpp"
#include "Spotify.hpp"
#include "Track.hpp"
#include "UserConfig.hpp"

/**
 * @brief The Player class
 * This class will be responsible to link the Spotify API to the GUI
 * and manager resources as list of playlist names, list of track for
 * each playlist, list of searched tracks by keyword
 */
class Player : public Spotify
{
  public:
    explicit Player(QObject *parent = nullptr);

    /**
     * @brief searchTrack
     * Search for a specific track in Spotify API
     * @param criteria
     * @param limit
     * @return
     */
    const QVector<Track> &searchTrack(const QString &criteria, int limit = 10);

    /**
     * @brief tracksBySearch
     * All tracks got from a search track
     * @return
     */
    const QVector<Track> &tracksBySearch() const;

    /**
     * @brief userConfig
     * @return
     */
    UserConfig &userConfig();

    /**
     * @brief setUserData
     * @param user_data
     */
    void setUserData(const UserData &user_data);

    /**
     * @brief playlistConfig
     * @see PlayslistConfig
     * @return
     */
    PlaylistConfig playlistConfig() const;

    /**
     * @brief playlistNames
     * @return
     */
    const QStringList &playlistNames();

    /**
     * @brief playlistTracks
     * all tracks presented in a playlist
     * @return
     */
    const QVector<Track> &playlistTracks() const;

    /**
     * @brief updatePlaylistTracks
     * Method used to update playlist table
     * @param playlist_name
     * @return
     */
    QVector<Track> updatePlaylistTracks(const QString playlist_name);

    using Spotify::playTrack;
    /**
     * @brief playTrack
     * play a specific track using Spotify API
     * @param track
     */
    void playTrack(const Track &track);

  private:
    /**
     * @brief setTracks
     * set tracks from a json object
     * @param json
     */
    void setTracks(const QJsonObject &json);

  private:
    QVector<Track> m_search_tracks;
    UserConfig m_user_config;
    PlaylistConfig m_playlist_config;
    QStringList m_playlist_names;
    QVector<Track> m_playlist_tracks;
};

#endif // PLAYER_HPP
