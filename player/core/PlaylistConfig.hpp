#ifndef PLAYLISTCONFIG_HPP
#define PLAYLISTCONFIG_HPP

#include <QStringList>
#include <fstream>
#include <map>

#include "Track.hpp"

//<PlaylistName, track_id, trackParameters>
typedef std::map<QString, std::map<QString, TrackParameters>> PlaylistData;

class PlaylistConfig
{
  public:
    PlaylistConfig();
    bool updated() const;
    const PlaylistData &data();
    void save(PlaylistData &playlist_data);
    void save(const QString &playlist_name);

  private:
    void save_playlist_data(std::ofstream &file, PlaylistData playlist_data);
    void update();

    void updatePlaylistData(const QStringList &str_csv);

  private:
    PlaylistData m_playlist_data;
    const std::string m_file_name = ".playlist_config";
    bool m_updated = false;
};

#endif // PLAYLISTCONFIG_HPP
