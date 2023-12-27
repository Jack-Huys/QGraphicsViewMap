#ifndef QGVMAPTILELOADERMANAGER_H
#define QGVMAPTILELOADERMANAGER_H

#include <QObject>


class QDir;
class QGVTile;
class QGVTileInfo;

#include "QGVTileOfflineLoader.h"
#include "QGVTileOnlineLoader.h"

class QGVMapTileLoaderManager : public QObject
{
    Q_OBJECT
public:
    QGVMapTileLoaderManager();
    ~QGVMapTileLoaderManager();

    void enableCaching();
    void disableCaching();
    void loadTile(QGVTileInfo info);

private slots:
    void offlineTileReady(QGVTile tile);
    void onlineTileReady(QGVTile tile);

private:
    QGVTileOnlineLoader	onlineTileLoader;
    QGVTileOfflineLoader offlineTileLoader;
    bool				cachingEnabled;
    QDir				cacheRepository;

signals:
    void tileLoaded(QGVTile tile);
};

#endif // QGVMAPTILELOADERMANAGER_H
