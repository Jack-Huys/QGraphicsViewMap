#include "QGVMapTileManager.h"
#include "QGVTile.h"
#include "QGVTileCoordinateUtility.h"

QGVMapTileManager::QGVMapTileManager(QGVMapQGView* view)
        :m_mapView(view)
{
    m_loadedTileSet = new QSet<QString>();
    m_mapMarkerList = new QList<QGVMapMarker>();
    m_currentTileType = STANDARD;

    QObject::connect
    (
        &m_tileLoaderManager,		SIGNAL(tileLoaded(QGVTile)),
        this,					SLOT(tileReady(QGVTile))
    );
    // Connect TileManager with View
    // Scene event
    QObject::connect
    (
        m_mapView,				SIGNAL(visibleSceneChanged(QRectF)),
        this,					SLOT(sceneChanged(QRectF))
    );
    // Zoom Up event
    QObject::connect
    (
        m_mapView,				SIGNAL(zoomUp()),
        this,					SLOT(zoomUp())
    );
    // Zoom Down event
    QObject::connect
    (
        m_mapView,				SIGNAL(zoomDown()),
        this,					SLOT(zoomDown())
    );
    // Load first tile
    //fovChanged(85.0, -180.0, -85.0, 180, 0, true);
}

void QGVMapTileManager::zoomUp()
{
    if (m_lastestZoomFactor > 0)
    {
        m_lastestZoomFactor--;
        m_mapView->clearScene();
        m_loadedTileSet->clear();
        fovChanged(m_lastestLatitude1, m_lastestLongitude1, m_lastestLatitude2, m_lastestLongitude2, m_lastestZoomFactor, true);
    }

    updateMarker();
    qDebug() << "ZoomUp " << m_lastestZoomFactor;
}

void QGVMapTileManager::zoomDown()
{
    if (m_lastestZoomFactor < 18)
    {
        m_lastestZoomFactor++;
        m_mapView->clearScene();
        m_loadedTileSet->clear();
        fovChanged(m_lastestLatitude1, m_lastestLongitude1, m_lastestLatitude2, m_lastestLongitude2, m_lastestZoomFactor, true);
    }

    updateMarker();
    qDebug() << "ZoomDown " << m_lastestZoomFactor;
}

void QGVMapTileManager::fovChanged(double lat1, double long1, double lat2, double long2, int zoom, bool center)
{
    m_lastestLatitude1 = lat1;
    m_lastestLongitude1 = long1;
    m_lastestLatitude2 = lat2;
    m_lastestLongitude2 = long2;
    m_lastestZoomFactor = zoom;

    int tileX1, tileX2, tileY1, tileY2;
    QGVTileCoordinateUtility::convertGeoToTileInteger(lat1, long1, zoom, tileX1, tileY1);
    QGVTileCoordinateUtility::convertGeoToTileInteger(lat2, long2, zoom, tileX2, tileY2);

    int x1 = qMin(tileX1, tileX2);
    int x2 = qMax(tileX1, tileX2);
    int y1 = qMin(tileY1, tileY2);
    int y2 = qMax(tileY1, tileY2);

    if(center == true)
    {
        double latCenter = lat1 + (lat2 - lat1) / 2.0;
        double longCenter = long1 + (long2 - long1) / 2.0;

        double xTile2, yTile2;
        QGVTileCoordinateUtility::convertGeoToTileDouble(latCenter, longCenter, zoom, xTile2, yTile2);
        QPointF center = QPointF(xTile2 * 256.0, yTile2 * 256.0);

        qDebug() << "New Center Tiles: " << xTile2 << " " << yTile2;
        qDebug() << "New Center Scene: " << xTile2 * 256.0 << " " << yTile2 * 256.0;
        qDebug() << "New Center Deg : " << longCenter << " " << latCenter;

        m_mapView->centerScene(center);
    }

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            QString str = QString("%1:%2:%3").arg(i).arg(j).arg(zoom);

            if (m_loadedTileSet->contains(str))
            {
                // Do nothing
            }
            else
            {
                // Insert value
                m_loadedTileSet->insert(str);
                // Load tile
                QGVTileInfo info(m_currentTileType, i, j, zoom);
                m_tileLoaderManager.loadTile(info);
            }
        }
    }
}

void QGVMapTileManager::sceneChanged(QRectF rectangle)
{
    // Convert scene coordinates to tile coordinates
    // Keep floating-point precision
    double startX = rectangle.x() / 256.0;
    double endX = ((rectangle.x() + rectangle.width()) / 256.0);

    double startY = rectangle.y() / 256.0;
    double endY = ((rectangle.y() + rectangle.height()) / 256.0);

    double lat1, lat2, long1, long2;
    QGVTileCoordinateUtility::convertTileDoubleToGeo(startX, startY, m_lastestZoomFactor, lat1, long1);
    QGVTileCoordinateUtility::convertTileDoubleToGeo(endX, endY, m_lastestZoomFactor, lat2, long2);

    fovChanged(lat1, long1, lat2, long2, m_lastestZoomFactor, false);
}

void QGVMapTileManager::changeTileType(TileTypeEnum type)
{
    if (type != m_currentTileType)
    {
        m_currentTileType = type;
        m_mapView->clearScene();
        m_loadedTileSet->clear();
        fovChanged(m_lastestLatitude1, m_lastestLongitude1, m_lastestLatitude2, m_lastestLongitude2, m_lastestZoomFactor, true);
    }
}

void QGVMapTileManager::addMarker(QGVMapMarker marker)
{
    if (!m_mapMarkerList->contains(marker))
    {
        m_mapMarkerList->append(marker);
    }
    updateMarker();
}

void QGVMapTileManager::removeMarker(QGVMapMarker marker)
{
    if (m_mapMarkerList->contains(marker))
    {
        m_mapMarkerList->removeOne(marker);
    }
    updateMarker();
}

void QGVMapTileManager::editMarker(QGVMapMarker marker)
{
    if (m_mapMarkerList->contains(marker))
    {
        int index = m_mapMarkerList->indexOf(marker);
        (*m_mapMarkerList)[index].m_latitude = marker.m_latitude;
        (*m_mapMarkerList)[index].m_longitude = marker.m_longitude;
    }
    updateMarker();
}

void QGVMapTileManager::updateMarker()
{
    m_mapView->clearAllMarker();

    for (int i = 0; i < m_mapMarkerList->size(); i++)
    {
        QGVMapMarker marker = m_mapMarkerList->at(i);

        double xCoord, yCoord;
        QGVTileCoordinateUtility::convertGeoToTileDouble(marker.m_latitude, marker.m_longitude, m_lastestZoomFactor, xCoord, yCoord);

        m_mapView->addMarker(marker.m_id, xCoord * 256.0, yCoord * 256.0, marker.m_image);
    }
}

void QGVMapTileManager::tileReady(QGVTile tile)
{
    if (tile.getTileInfo().getTileType() == m_currentTileType)
    {
        if (tile.getTileInfo().getZoom() == m_lastestZoomFactor)
        {
            m_mapView->addTile(
                tile.getImage(),
                tile.getTileInfo().getX(),
                tile.getTileInfo().getY(),
                256
                );
        }
        else
        {
            qDebug() << "Wrong zoom factor";
        }
    }
}
