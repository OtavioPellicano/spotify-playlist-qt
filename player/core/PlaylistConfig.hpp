#ifndef PLAYLISTCONFIG_HPP
#define PLAYLISTCONFIG_HPP

#include <QStringList>
#include <algorithm>
#include <fstream>
#include <functional>
#include <map>

#include "Track.hpp"

//<<Playlist name, track_id>, trackParameters>
typedef std::map<std::pair<QString, QString>, TrackParameters> PlaylistData;

/**
 * @brief The PlaylistConfig class
 * This class manager PlaylistData geting the current Playlist data (saved in .playlist_config file),
 * add and remove tracks/playlist
 */
class PlaylistConfig
{
  public:
    PlaylistConfig();

    /**
     * @brief data
     * This method will return the PlaylistData updated
     * @return
     */
    const PlaylistData &data();

    /**
     * @brief save
     * Save new Playlist data in the file
     * @param playlist_data
     */
    void save(PlaylistData &playlist_data);

    /**
     * @brief removePlaylist
     * Remove Playlist from the file
     * @param playlist_name
     */
    void removePlaylist(const QString &playlist_name);

    /**
     * @brief removeTrackFromPlaylist
     * Remove a track from playlist
     * @param playlist_name
     * @param track_id
     */
    void removeTrackFromPlaylist(const QString &playlist_name, const QString &track_id);

  private:
    void savePlaylistData(PlaylistData &playlist_data);

    /**
     * @brief update
     * @see UserConfig::update
     */
    void update();

    /**
     * @brief updatePlaylistData
     * format playlist string got from file
     * @param str_csv
     */
    void updatePlaylistData(const QStringList &str_csv);

  private:
    PlaylistData m_playlist_data;
    const std::string m_file_name = ".playlist_config";
    const QString m_sep = "||";
};

#endif // PLAYLISTCONFIG_HPP
