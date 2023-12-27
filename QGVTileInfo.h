#ifndef QGVTILEINFO_H
#define QGVTILEINFO_H

enum TileTypeEnum
{
    STANDARD = 10,
    CYCLE = 100,
    CYCLE_TRANSPORT = 1000
};

class QGVTileInfo
{
public:
    QGVTileInfo();
    QGVTileInfo(TileTypeEnum type, int x, int y, int zoom);

    TileTypeEnum getTileType() const;
    void	 setTileType(TileTypeEnum type);
    int		 getX() const;
    void	 setX(int x);
    int	     getY() const;
    void	 setY(int y);
    int	     getZoom() const;
    void	 setZoom(int zoom);

private:
    TileTypeEnum	tileType;
    int			x;
    int			y;
    int			zoom;
};

#endif // QGVTILEINFO_H
