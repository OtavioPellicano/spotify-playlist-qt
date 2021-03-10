#ifndef TRACK_HPP
#define TRACK_HPP

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Track;

/**
 * @brief The TrackParameters struct
 */
struct TrackParameters
{
    QString name, id, album, album_id, artist, artist_id, uri;
    int duration = 0; // ms

    QString toString(const QString &sep = "||")
    {
        return QStringList({name, id, album, album_id, artist, artist_id, QString::number(duration), uri}).join(sep);
    }
};

/**
 * @brief The Track class
 * This class got a Json item and tranform to TrackParameters
 */
class Track
{
  public:
    explicit Track(const QJsonObject &item);

    Track(const TrackParameters &track_parameters);

    TrackParameters trackParameters() const;

  private:
    TrackParameters m_track_parameters;
};

#endif // TRACK_HPP
