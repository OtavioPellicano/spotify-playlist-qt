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

TrackParameters track_3{
    "Eu Sei",
    "4SMzisVrGggLbPc5TII5pa",
    "Eu Sei",
    "19CoivK6bPGL0SC1RZEKfa",
    "Vk Mac",
    "62T0up856eHZQ8BE6V6fJs",
    "spotify:track:4SMzisVrGggLbPc5TII5pa",
    209747};
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
    void test_track();
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

void TestPlayer::test_track()
{
    auto track_3 = Track(TrackSamples::track_3);
    QVERIFY(track_3.trackParameters() == TrackSamples::track_3);

    QByteArray json =
        "{\n    \"album\": {\n        \"album_type\": \"single\",\n        \"artists\": [\n            {\n             "
        "   \"external_urls\": {\n                    \"spotify\": "
        "\"https://open.spotify.com/artist/62T0up856eHZQ8BE6V6fJs\"\n                },\n                \"href\": "
        "\"https://api.spotify.com/v1/artists/62T0up856eHZQ8BE6V6fJs\",\n                \"id\": "
        "\"62T0up856eHZQ8BE6V6fJs\",\n                \"name\": \"Vk Mac\",\n                \"type\": \"artist\",\n   "
        "             \"uri\": \"spotify:artist:62T0up856eHZQ8BE6V6fJs\"\n            },\n            {\n              "
        "  \"external_urls\": {\n                    \"spotify\": "
        "\"https://open.spotify.com/artist/6ACyNjY4S7gBFxB4fcmJEQ\"\n                },\n                \"href\": "
        "\"https://api.spotify.com/v1/artists/6ACyNjY4S7gBFxB4fcmJEQ\",\n                \"id\": "
        "\"6ACyNjY4S7gBFxB4fcmJEQ\",\n                \"name\": \"Chief\",\n                \"type\": \"artist\",\n    "
        "            \"uri\": \"spotify:artist:6ACyNjY4S7gBFxB4fcmJEQ\"\n            }\n        ],\n        "
        "\"external_urls\": {\n            \"spotify\": \"https://open.spotify.com/album/19CoivK6bPGL0SC1RZEKfa\"\n    "
        "    },\n        \"href\": \"https://api.spotify.com/v1/albums/19CoivK6bPGL0SC1RZEKfa\",\n        \"id\": "
        "\"19CoivK6bPGL0SC1RZEKfa\",\n        \"images\": [\n            {\n                \"height\": 640,\n         "
        "       \"url\": \"https://i.scdn.co/image/ab67616d0000b273d44a718140a9dd2c71810ffb\",\n                "
        "\"width\": 640\n            },\n            {\n                \"height\": 300,\n                \"url\": "
        "\"https://i.scdn.co/image/ab67616d00001e02d44a718140a9dd2c71810ffb\",\n                \"width\": 300\n       "
        "     },\n            {\n                \"height\": 64,\n                \"url\": "
        "\"https://i.scdn.co/image/ab67616d00004851d44a718140a9dd2c71810ffb\",\n                \"width\": 64\n        "
        "    }\n        ],\n        \"name\": \"Eu Sei\",\n        \"release_date\": \"2021-01-28\",\n        "
        "\"release_date_precision\": \"day\",\n        \"total_tracks\": 1,\n        \"type\": \"album\",\n        "
        "\"uri\": \"spotify:album:19CoivK6bPGL0SC1RZEKfa\"\n    },\n    \"artists\": [\n        {\n            "
        "\"external_urls\": {\n                \"spotify\": "
        "\"https://open.spotify.com/artist/62T0up856eHZQ8BE6V6fJs\"\n            },\n            \"href\": "
        "\"https://api.spotify.com/v1/artists/62T0up856eHZQ8BE6V6fJs\",\n            \"id\": "
        "\"62T0up856eHZQ8BE6V6fJs\",\n            \"name\": \"Vk Mac\",\n            \"type\": \"artist\",\n           "
        " \"uri\": \"spotify:artist:62T0up856eHZQ8BE6V6fJs\"\n        },\n        {\n            \"external_urls\": "
        "{\n                \"spotify\": \"https://open.spotify.com/artist/6ACyNjY4S7gBFxB4fcmJEQ\"\n            },\n  "
        "          \"href\": \"https://api.spotify.com/v1/artists/6ACyNjY4S7gBFxB4fcmJEQ\",\n            \"id\": "
        "\"6ACyNjY4S7gBFxB4fcmJEQ\",\n            \"name\": \"Chief\",\n            \"type\": \"artist\",\n            "
        "\"uri\": \"spotify:artist:6ACyNjY4S7gBFxB4fcmJEQ\"\n        }\n    ],\n    \"disc_number\": 1,\n    "
        "\"duration_ms\": 209747,\n    \"explicit\": false,\n    \"external_ids\": {\n        \"isrc\": "
        "\"BCIGI2100001\"\n    },\n    \"external_urls\": {\n        \"spotify\": "
        "\"https://open.spotify.com/track/4SMzisVrGggLbPc5TII5pa\"\n    },\n    \"href\": "
        "\"https://api.spotify.com/v1/tracks/4SMzisVrGggLbPc5TII5pa\",\n    \"id\": \"4SMzisVrGggLbPc5TII5pa\",\n    "
        "\"is_local\": false,\n    \"is_playable\": true,\n    \"name\": \"Eu Sei\",\n    \"popularity\": 45,\n    "
        "\"preview_url\": "
        "\"https://p.scdn.co/mp3-preview/"
        "be0ef482cad02a525dbd6a49002ea8706bb42d1f?cid=d3a56a29ae1e429b8677f06bdf972ca4\",\n    \"track_number\": 1,\n  "
        "  \"type\": \"track\",\n    \"uri\": \"spotify:track:4SMzisVrGggLbPc5TII5pa\"\n}\n";

    auto track_3_json = Track(QJsonDocument::fromJson(json).object());
    QVERIFY(track_3_json.trackParameters() == track_3.trackParameters());
}

QTEST_MAIN(TestPlayer)

#include "tst_player.moc"
