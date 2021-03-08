#include "Spotify.hpp"

Spotify::Spotify(QObject *parent)
    : QObject(parent)
{

    this->updateSpotifyUserConfig();

    connect(&m_spotify_api, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(&m_spotify_api, &QOAuth2AuthorizationCodeFlow::granted, this, &Spotify::granted);

    m_spotify_api.grant();
}

void Spotify::granted()
{
    qDebug() << "granted!";
    m_is_granted = true;
}

void Spotify::statusChanged(QAbstractOAuth::Status status)
{
    switch (status)
    {
    case QAbstractOAuth::Status::Granted:
        this->granted();
        break;
    case QAbstractOAuth::Status::NotAuthenticated:
        qDebug() << "NotAuthenticated!";
        m_is_granted = false;
        break;
    case QAbstractOAuth::Status::RefreshingToken:
        qDebug() << "RefreshingToken!";
        // Token update
        m_spotify_api.post(QUrl(m_user_config.userData().access_token_url));
        m_is_granted = true;
        break;
    default:
        break;
    }
}

void Spotify::updateSpotifyUserConfig()
{
    m_reply_handler = std::make_unique<QOAuthHttpServerReplyHandler>(8080, this);
    auto user_data = m_user_config.userData();

    m_spotify_api.setReplyHandler(m_reply_handler.get());
    m_spotify_api.setAuthorizationUrl(QUrl(user_data.auth_url));
    m_spotify_api.setAccessTokenUrl(QUrl(user_data.access_token_url));
    m_spotify_api.setClientIdentifier(user_data.client_id);
    m_spotify_api.setClientIdentifierSharedKey(user_data.client_secret);

    QStringList scopes = {
        "playlist-read-collaborative",
        "playlist-read-private",
        "playlist-modify-private",
        "playlist-modify-public",
        "user-follow-read",
        "user-follow-modify",
        "user-library-modify",
        "user-library-read",
        "user-modify-playback-state",
        "user-read-currently-playing",
        "user-read-playback-state",
        "user-read-private",
        "user-read-recently-played",
        "streaming",
        "user-read-email",
        "user-top-read"};

    m_spotify_api.setScope(scopes.join(' '));
}

QJsonObject Spotify::search(const QString &criteria, SearchType search_type, int limit)
{
    auto q_type = QString("");
    switch (search_type)
    {
        //    case SearchType::album:
        //        q_type = "album";
        //        break;
        //    case SearchType::artist:
        //        q_type = "artist";
        //        break;
    case SearchType::track:
        q_type = "track";
        break;
    }

    return this->requestGet(
        "search?q=" + criteria + "&type=" + q_type + "&limit=" + QString::number(limit) + "&market=from_token");
}

QJsonObject Spotify::requestGet(const QString &parameters)
{
    auto reply = m_spotify_api.get(QUrl(m_user_config.userData().base_url + "/" + parameters));

    while (!reply->isFinished())
    {
        QCoreApplication::processEvents();
    }

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return QJsonObject();
    }
    else
    {
        auto data = reply->readAll();
        qDebug() << data;
        return QJsonDocument::fromJson(data).object();
    }
}

QJsonObject Spotify::searchTrack(const QString &criteria, int limit)
{
    return this->search(criteria, SearchType::track, limit);
}

bool Spotify::isGranted() const
{
    return m_is_granted;
}
