#include "QGVTileCoordinateUtility.h"

#include <cmath>

void QGVTileCoordinateUtility::convertGeoToTileInteger(double latitudeDegree, double longitudeDegree, int zoomLevel, int& xTile, int& yTile)
{
    static const double PI = 3.14159;

    int n = (int) pow(2.0, zoomLevel);

    double latitudeRadians = latitudeDegree * 2.0 * PI / 360.0;

    xTile = (int)(n *((longitudeDegree + 180) / 360.0));

    double secanteValue = 1.0 / cos(latitudeRadians);
    double tangenteValue = tan(latitudeRadians);

    yTile = (int)(n * (1 - (log(tangenteValue + secanteValue) / PI)) / 2.0);
}

void QGVTileCoordinateUtility::convertGeoToTileDouble(double latitudeDegree, double longitudeDegree, int zoomLevel, double& xTile, double& yTile)
{
    static const double PI = 3.14159;

    int n = (int) pow(2.0, zoomLevel);

    double latitudeRadians = latitudeDegree * 2.0 * PI / 360.0;

    xTile = (n *((longitudeDegree + 180.0) / 360.0));

    double secanteValue = 1.0 / cos(latitudeRadians);
    double tangenteValue = tan(latitudeRadians);

    yTile = (n * (1 - (log(tangenteValue + secanteValue) / PI)) / 2.0);
}

void QGVTileCoordinateUtility::convertTileToGeo(int xTile, int yTile, int zoomLevel, double& latitudeDegree, double& longitudeDegree)
{
    static const double PI = 3.14159;

    longitudeDegree = xTile / pow(2.0, zoomLevel) * 360.0 - 180;

    double n = PI - 2.0 * PI * yTile / pow(2.0, zoomLevel);

    latitudeDegree = 180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
}

void QGVTileCoordinateUtility::convertTileDoubleToGeo(double xTile, double yTile, int zoomLevel, double& latitudeDegree, double& longitudeDegree)
{
    static const double PI = 3.14159;

    longitudeDegree = xTile / pow(2.0, zoomLevel) * 360.0 - 180;

    double n = PI - 2.0 * PI * yTile / pow(2.0, zoomLevel);

    latitudeDegree = 180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
}

void QGVTileCoordinateUtility::getLongitudeRatio(int zoomLevel, double& longitudeRatio)
{

}

void QGVTileCoordinateUtility::getLatitudeRatio(int zoomLevel, double& latitudeRatio)
{

}
