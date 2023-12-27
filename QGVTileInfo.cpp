#include "QGVTileInfo.h"

QGVTileInfo::QGVTileInfo()
{
    this->tileType = STANDARD;
    this->x = 0;
    this->y = 0;
    this->zoom = 0;
}

QGVTileInfo::QGVTileInfo(TileTypeEnum type, int x, int y, int zoom)
{
    this->tileType = type;
    this->x = x;
    this->y = y;
    this->zoom = zoom;
}

TileTypeEnum QGVTileInfo::getTileType() const
{
    return tileType;
}

void QGVTileInfo::setTileType(TileTypeEnum type)
{
    this->tileType = type;
}

int QGVTileInfo::getX() const
{
    return x;
}

void QGVTileInfo::setX(int x)
{
    this->x = x;
}

int QGVTileInfo::getY() const
{
    return y;
}

void QGVTileInfo::setY(int y)
{
    this->y = y;
}

int QGVTileInfo::getZoom() const
{
    return zoom;
}

void QGVTileInfo::setZoom(int zoom)
{
    this->zoom = zoom;
}


