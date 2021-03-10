#ifndef PLAYLISTCONFIG_HPP
#define PLAYLISTCONFIG_HPP

#include <QStringList>
#include <algorithm>
#include <fstream>
#include <functional>
#include <map>

#include "Track.hpp"

//<Playlist, track_id>, trackParameters
typedef std::map<std::pair<QString, QString>, TrackParameters> PlaylistData;

class PlaylistConfig
{
  public:
    PlaylistConfig();
    const PlaylistData &data();
    void save(PlaylistData &playlist_data);
    void removePlaylist(const QString &playlist_name);
    void removeTrackFromPlaylist(const QString &playlist_name, const QString &track_id);

  private:
    void savePlaylistData(PlaylistData &playlist_data);
    void update();

    void updatePlaylistData(const QStringList &str_csv);

  private:
    PlaylistData m_playlist_data;
    const std::string m_file_name = ".playlist_config";
    const QString m_sep = "||";
};

#endif // PLAYLISTCONFIG_HPP
