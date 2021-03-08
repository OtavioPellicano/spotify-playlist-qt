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
    void granted();
    void statusChanged(QAbstractOAuth::Status status);

  private:
    void update_spotify_user_config();
    enum class SearchType
    {
        //        artist,
        //        album,
        track
    };
    QJsonObject search(const QString &criteria, SearchType search_type, int limit);
    QJsonObject request_get(const QString &parameters);

  public:
    //    QJsonObject search_artist(const QString &criteria);
    //    QJsonObject search_album(const QString &criteria);
    QJsonObject search_track(const QString &criteria, int limit);

    bool is_granted() const;

  private:
    UserConfig m_user_config;
    QOAuth2AuthorizationCodeFlow m_spotify_api;
    std::unique_ptr<QOAuthHttpServerReplyHandler> m_reply_handler;
    bool m_is_granted = false;
};

#endif // AUTH_H
