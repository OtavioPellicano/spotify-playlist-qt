#include "Track.hpp"

Track::Track(const QJsonObject &item)
{
    auto track = item.contains("track") ? item["track"].toObject() : item;

    m_track_parameters.id = track.contains("id") ? track["id"].toString() : "0";
    m_track_parameters.album =
        track.contains("album") ? track["album"].toObject()["name"].toString() : "(desconhecido)";
    m_track_parameters.album_id = track.contains("album") ? track["album"].toObject()["id"].toString() : "0";
    m_track_parameters.artist =
        track.contains("artists") ? track["artists"].toArray()[0].toObject()["name"].toString() : "(desconhecido)";
    m_track_parameters.artist_id =
        track.contains("artists") ? track["artists"].toArray()[0].toObject()["id"].toString() : "0";
    m_track_parameters.name = track.contains("name") ? track["name"].toString() : "(desconhecido)";
    m_track_parameters.duration = track.contains("duration_ms") ? track["duration_ms"].toInt() : 0;

    qDebug() << "TRACK INFO:";
    qDebug() << m_track_parameters.toString();
}

TrackParameters Track::trackParameters() const
{
    return m_track_parameters;
}
