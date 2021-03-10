#ifndef AUTH_H
#define AUTH_H

#include <QObject>

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QOAuth2AuthorizationCodeFlow>
#include <QtNetwork>
#include <QtNetworkAuth>
#include <memory>

#include "UserConfig.hpp"

class Spotify : public QObject
{
    Q_OBJECT
  public:
    explicit Spotify(QObject *parent = nullptr);

  private slots:
    void on_granted();
    void statusChanged(QAbstractOAuth::Status status);

  signals:
    void granted(bool);

  private:
    void updateSpotifyUserConfig();
    enum class SearchType
    {
        //        artist,
        //        album,
        track
    };
    QJsonObject search(const QString &criteria, SearchType search_type, int limit);
    QJsonObject requestGet(const QString &parameters);

  public:
    //    QJsonObject search_artist(const QString &criteria);
    //    QJsonObject search_album(const QString &criteria);
    QJsonObject searchTrack(const QString &criteria, int limit);

    void connectToAPI();

  private:
    UserConfig m_user_config;
    QOAuth2AuthorizationCodeFlow m_spotify_api;
    std::unique_ptr<QOAuthHttpServerReplyHandler> m_reply_handler;
};

#endif // AUTH_H
