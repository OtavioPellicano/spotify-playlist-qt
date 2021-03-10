#include "Spotify.hpp"

Spotify::Spotify(QObject *parent)
    : QObject(parent)
{
    connect(&m_spotify_api, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(&m_spotify_api, &QOAuth2AuthorizationCodeFlow::granted, this, &Spotify::on_granted);
}

void Spotify::on_granted()
{
    if (m_spotify_api.status() == QAbstractOAuth::Status::Granted)
    {
        qDebug() << "granted!";
        emit granted(true);
        return;
    }
    emit granted(false);
}

void Spotify::statusChanged(QAbstractOAuth::Status status)
{
    switch (status)
    {
    case QAbstractOAuth::Status::Granted:
        this->on_granted();
        break;
    case QAbstractOAuth::Status::NotAuthenticated:
        qDebug() << "NotAuthenticated!";
        emit granted(false);
        break;
    case QAbstractOAuth::Status::RefreshingToken:
        qDebug() << "RefreshingToken!";
        // Token update
        m_spotify_api.post(QUrl(m_user_config.data().access_token_url));
        break;
    default:
        break;
    }
}

void Spotify::updateSpotifyUserConfig()
{
    m_reply_handler = std::make_unique<QOAuthHttpServerReplyHandler>(8080, this);
    auto user_data = m_user_config.data();

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

    return this->request(
        RequestType::get,
        "search?q=" + criteria + "&type=" + q_type + "&limit=" + QString::number(limit) + "&market=from_token");
}

QJsonObject Spotify::request(RequestType request_type, const QString &parameters, const QJsonDocument &body)
{

    auto url = QUrl(m_user_config.data().base_url + "/" + parameters);

    auto reply = request_type == RequestType::get ? m_spotify_api.get(url) : m_spotify_api.put(url, body.toJson());

    while (!reply->isFinished())
    {
        QCoreApplication::processEvents();
    }

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString() << ": " << reply->error();
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

void Spotify::playTrack(const QString &uri)
{
    QJsonDocument body({
        QPair<QString, QJsonArray>("context_uri", {QJsonArray::fromStringList(QStringList(uri))}),
    });

    this->request(RequestType::put, "me/player/play", body);
}

void Spotify::connectToAPI()
{
    this->updateSpotifyUserConfig();
    m_spotify_api.grant();
}
