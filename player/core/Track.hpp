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

    QString toString(const QString &sep = ",")
    {
        return QStringList({name, id, album, album_id, artist, artist_id, QString::number(duration)}).join(sep);
    }
};

class Track
{
  public:
    explicit Track(const QJsonObject &item);

    TrackParameters trackParameters() const;

  private:
    TrackParameters m_track_parameters;
};

#endif // TRACK_HPP
