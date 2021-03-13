#include <QCoreApplication>
#include <QtTest>

// add necessary includes here
#include "PlaylistConfig.hpp"
#include "UserConfig.hpp"

bool operator==(const TrackParameters &track_1, const TrackParameters &track_2)
{
    return track_1.album == track_2.album && track_1.album_id == track_2.album_id && track_1.artist == track_2.artist &&
           track_1.artist_id == track_2.artist_id && track_1.duration == track_2.duration && track_1.id == track_2.id &&
           track_1.name == track_2.name && track_1.uri == track_2.uri;
}

bool operator!=(const TrackParameters &track_1, const TrackParameters &track_2)
{
    return !(track_1 == track_2);
}

namespace TrackSamples
{

TrackParameters track_1{
    "OUTRO PATAMAR",
    "48zE1jY1K1oqjpD3G6UGfH",
    "OUTRO PATAMAR",
    "1nb3EIZXO75bxWDz0Agxfo",
    "MC Cabelinho",
    "1WQBwwssN6r8DSjUlkyUGW",
    "spotify:track:48zE1jY1K1oqjpD3G6UGfH",
    206608};

TrackParameters track_2{
    "Porque Eu Sei Que É Amor - Acústico",
    "2l9m7wvaWabz7NhaTwBFbZ",
    "Porque Eu Sei Que É Amor (Acústico)",
    "3cxsRe4dYedyVZ5j0JYhSu",
    "Titãs",
    "2euX7vCVnJy3TVEGfc0RCl",
    "spotify:track:2l9m7wvaWabz7NhaTwBFbZ",
    203625};

} // namespace TrackSamples

class TestPlayer : public QObject
{
    Q_OBJECT

  public:
    TestPlayer();
    ~TestPlayer();

  private slots:
    void test_user_config();
    void test_playlist_config();
};

TestPlayer::TestPlayer()
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::test_user_config()
{
    UserConfig user_config;
    user_config.save("Otavio", "Pellicano");
    auto user_data = user_config.data();

    QVERIFY(user_data.client_id == "Otavio");
    QVERIFY(user_data.client_secret == "Pellicano");
    QVERIFY(user_data.access_token_url == "https://accounts.spotify.com/api/token");
    QVERIFY(user_data.auth_url == "https://accounts.spotify.com/authorize");
    QVERIFY(user_data.api_url == "https://api.spotify.com");
    QVERIFY(user_data.api_version == "v1");
    QVERIFY(user_data.base_url == "https://api.spotify.com/v1");
}

void TestPlayer::test_playlist_config()
{
    auto playlist_name_1 = QString("Otavio");
    auto playlist_name_2 = QString("Pellicano");

    auto track_1 = TrackSamples::track_1;
    auto track_2 = TrackSamples::track_2;

    auto tracks_sample = [&]() -> PlaylistData {
        auto tracks = PlaylistData();
        tracks[Key(playlist_name_1, track_1.id)] = track_1;
        tracks[Key(playlist_name_1, track_2.id)] = track_2;

        tracks[Key(playlist_name_2, track_1.id)] = track_1;
        tracks[Key(playlist_name_2, track_2.id)] = track_2;

        return tracks;
    };

    auto tracks = tracks_sample();

    auto playlist_config = PlaylistConfig();
    playlist_config.save(tracks);

    // Verify if all tracks were add
    auto data = playlist_config.data();
    QVERIFY(data.find({playlist_name_1, track_1.id})->second == track_1);
    QVERIFY(data.find({playlist_name_1, track_2.id})->second == track_2);
    QVERIFY(data.find({playlist_name_2, track_1.id})->second == track_1);
    QVERIFY(data.find({playlist_name_2, track_2.id})->second == track_2);

    // Remove Track from playlist
    playlist_config.removeTrackFromPlaylist(playlist_name_1, track_1.id);
    data = playlist_config.data();
    QVERIFY(data.find({playlist_name_1, track_1.id}) == data.end());
    QVERIFY(data.find({playlist_name_1, track_2.id})->second == track_2);
    QVERIFY(data.size() == 3);

    // Remove Playlist
    playlist_config.removePlaylist(playlist_name_2);
    data = playlist_config.data();
    QVERIFY(data.find({playlist_name_2, track_1.id}) == data.end());
    QVERIFY(data.find({playlist_name_2, track_2.id}) == data.end());
    QVERIFY(data.size() == 1);
}

QTEST_MAIN(TestPlayer)

#include "tst_player.moc"
