#ifndef QGVTILE_H
#define QGVTILE_H

#include <QImage>
#include "QGVTileInfo.h"


class QGVTile
{
public:
    QGVTile();
    QGVTile(QGVTileInfo info, QImage image);
    ~QGVTile();

    QGVTileInfo getTileInfo() const;
    void	 setTileInfo(QGVTileInfo tileInfo);
    QImage	 getImage() const;
    void	 setImage(QImage image);

private:
    QGVTileInfo m_tileInfo;
    QImage	 m_tileImage;
};

#endif // QGVTILE_H
