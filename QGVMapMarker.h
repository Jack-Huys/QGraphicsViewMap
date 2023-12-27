#ifndef QGVMAPMARKER_H
#define QGVMAPMARKER_H


#include <QImage>

class QGVMapMarker
{
public:
    QGVMapMarker();
    ~QGVMapMarker();

public:
    QImage m_image;
    int m_id;
    double m_latitude;
    double m_longitude;
    bool operator ==(const QGVMapMarker & m) const;

};


#endif // QGVMAPMARKER_H
