#include "QGVTileOfflineLoader.h"

QGVTileOfflineLoader::QGVTileOfflineLoader()
{

}

QGVTileOfflineLoader::~QGVTileOfflineLoader()
{

}

QDir QGVTileOfflineLoader::getRepository()
{
    return cacheRepository;
}

void QGVTileOfflineLoader::setRepository(QDir directory)
{
    this->cacheRepository = directory;
}

void QGVTileOfflineLoader::loadTile(QGVTileInfo info)
{
    if (isTileAvailable(info))
    {
        QString filename = getFilenameFromInfo(info, cacheRepository);
        QImage image(filename);

        QGVTile tile(info, image);

        emit offlineTileLoaded(tile);
    }
}

bool QGVTileOfflineLoader::isTileAvailable(QGVTileInfo info)
{
    if (cacheRepository.exists())
    {
        QFile file(getFilenameFromInfo(info, cacheRepository));
        return file.exists();
    }
    else
    {
        return false;
    }
}

QString QGVTileOfflineLoader::getFilenameFromInfo(QGVTileInfo info, QDir directory)
{
    QString tileTypeFolder = QString("TileType %1").arg(info.getTileType());
    QString zoomFolder = QString("ZoomLevel %1").arg(info.getZoom());
    QString imageName = QString("%1x_%2y_%3z.png").arg(info.getX()).arg(info.getY()).arg(info.getZoom());

    QString fileName = directory.absolutePath() + "//" + tileTypeFolder + "//" + zoomFolder + "//" + imageName;
    return fileName;
}
