#include "QGVTile.h"

QGVTile::QGVTile()
{

}

QGVTile::QGVTile(QGVTileInfo info, QImage image)
{
    this->m_tileInfo = info;
    this->m_tileImage = image;
}

QGVTile::~QGVTile()
{

}

QGVTileInfo QGVTile::getTileInfo() const
{
    return m_tileInfo;
}

void QGVTile::setTileInfo(QGVTileInfo tileInfo)
{
    this->m_tileInfo = tileInfo;
}

QImage QGVTile::getImage() const
{
    return m_tileImage;
}

void QGVTile::setImage(QImage image)
{
    this->m_tileImage = image;
}
