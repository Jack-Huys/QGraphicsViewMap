#ifndef QGVTILECOORDINATEUTILITY_H
#define QGVTILECOORDINATEUTILITY_H


class QGVTileCoordinateUtility
{
public:
    static void convertGeoToTileInteger(double latitudeDegree, double longitudeDegree, int zoomLevel, int& xTile, int& yTile);
    static void convertGeoToTileDouble(double latitudeDegree, double longitudeDegree, int zoomLevel, double& xTile, double& yTile);
    static void convertTileToGeo(int xTile, int yTile, int zoomLevel, double& latitudeDegree, double& longitudeDegree);
    static void convertTileDoubleToGeo(double xTile, double yTile, int zoomLevel, double& latitudeDegree, double& longitudeDegree);

    static void getLongitudeRatio(int zoomLevel, double& longitudeRatio);
    static void getLatitudeRatio(int zoomLevel, double& latitudeRatio);
};

#endif // QGVTILECOORDINATEUTILITY_H
