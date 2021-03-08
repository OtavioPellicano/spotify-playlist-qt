#ifndef TRACK_HPP
#define TRACK_HPP

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Track;

struct TrackParameters
{
    QString name, id, album, album_id, artist, artist_id;
    int duration = 0; // ms

  private:
    // help to debug
    QString to_string(const QString &sep = ",")
    {
        return QStringList({name, id, album, album_id, artist, artist_id, QString::number(duration)}).join(sep);
    }
    friend Track;
};

class Track
{
  public:
    explicit Track(const QJsonObject &item);

    TrackParameters track_parameters() const;

  private:
    TrackParameters m_track_parameters;
};

#endif // TRACK_HPP
