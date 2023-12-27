#ifndef QGVTILEOFFLINELOADER_H
#define QGVTILEOFFLINELOADER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include "QGVTile.h"

class QGVTileOfflineLoader : public QObject
{
    Q_OBJECT
public:
    QGVTileOfflineLoader();
    ~QGVTileOfflineLoader();

    QDir	getRepository();
    void	setRepository(QDir directory);

    void	loadTile(QGVTileInfo info);
    bool	isTileAvailable(QGVTileInfo info);

    // should move this to a utility class
    QString getFilenameFromInfo(QGVTileInfo info, QDir directory);

signals:
    void	offlineTileLoaded(QGVTile tile);

private:
    QDir	cacheRepository;
};

#endif // QGVTILEOFFLINELOADER_H
