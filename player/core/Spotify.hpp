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

/**
 * @brief The Spotify class
 * This class is handdle the Spotify API, control the authorization flow,
 * making requests to search tracks from keyword and send request to play
 * a specific song
 */
class Spotify : public QObject
{
    Q_OBJECT
  public:
    explicit Spotify(QObject *parent = nullptr);

    /**
     * @brief connectToAPI
     * Update the user informations and grant
     */
    void connectToAPI();

  private slots:
    void on_granted();
    void statusChanged(QAbstractOAuth::Status status);

  signals:
    void granted(bool);

  private:
    /**
     * @brief updateSpotifyUserConfig
     * apdate Spotify API with user informations
     */
    void updateSpotifyUserConfig();

    enum class SearchType
    {
        //        artist,
        //        album,
        track
    };

    /**
     * @brief search
     * Search for a specific song
     * @param criteria
     * the keyword used to search
     * @param search_type
     * @param limit
     * @return
     */
    QJsonObject search(const QString &criteria, SearchType search_type, int limit);

    enum class RequestType
    {
        get,
        put
    };
    /**
     * @brief request
     * make get or put request
     * @param request_type
     * @param parameters
     * @param body
     * @return
     */
    QJsonObject request(
        RequestType request_type, const QString &parameters, const QJsonDocument &body = QJsonDocument());

  protected:
    //    QJsonObject search_artist(const QString &criteria);
    //    QJsonObject search_album(const QString &criteria);

    /**
     * @brief searchTrack
     * Search for a track
     * @param criteria
     * @param limit
     * @return
     */
    QJsonObject searchTrack(const QString &criteria, int limit);

    /**
     * @brief playTrack
     * play a track given a track uri
     * @param track_id
     */
    void playTrack(const QString &uri);

  private:
    UserConfig m_user_config;
    QOAuth2AuthorizationCodeFlow m_spotify_api;
    std::unique_ptr<QOAuthHttpServerReplyHandler> m_reply_handler;
};

#endif // AUTH_H
