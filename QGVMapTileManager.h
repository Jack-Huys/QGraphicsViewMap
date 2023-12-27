#ifndef QGVMAPTILEMANAGER_H
#define QGVMAPTILEMANAGER_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include <QList>

#include "QGVMapQGView.h"
#include "QGVMapTileLoaderManager.h"
#include "QGVMapMarker.h"

class QGVTile;

class QGVMapTileManager : public QObject
{
    Q_OBJECT

public:
    QGVMapTileManager(QGVMapQGView* view);

public slots:
    void zoomUp();
    void zoomDown();
    void fovChanged(double lat1, double long1, double lat2, double long2, int zoom, bool center);
    void sceneChanged(QRectF rectangle);
    void changeTileType(TileTypeEnum type);

    void addMarker(QGVMapMarker marker);
    void removeMarker(QGVMapMarker marker);
    void editMarker(QGVMapMarker marker);
    void updateMarker();

private slots:
    void tileReady(QGVTile tile);

signals:
    void clearScene();

private:

    QGVMapTileLoaderManager m_tileLoaderManager;
    QGVMapQGView* m_mapView;
    TileTypeEnum m_currentTileType;
    QSet<QString>* m_loadedTileSet;
    QList<QGVMapMarker>* m_mapMarkerList;

    float   m_lastestLatitude1;
    float	m_lastestLongitude1;
    float	m_lastestLatitude2;
    float	m_lastestLongitude2;
    int		m_lastestZoomFactor;
};

#endif // QGVMAPTILEMANAGER_H
