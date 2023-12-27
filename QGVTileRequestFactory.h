#ifndef QGVTILEREQUESTFACTORY_H
#define QGVTILEREQUESTFACTORY_H
#include "QGVDownloadTileRequest.h"

class QGVTileRequestFactory
{
public:
    QGVTileRequestFactory();
    ~QGVTileRequestFactory();

    QGVDownloadTileRequest* createTileRequest(QGVTileInfo info);

private:
    static const QString STANDARD_MAP_SERVER_A;
    static const QString STANDARD_MAP_SERVER_B;
    static const QString STANDARD_MAP_SERVER_C;

    static const QString CYCLE_MAP_SERVER_A;
    static const QString CYCLE_MAP_SERVER_B;
    static const QString CYCLE_MAP_SERVER_C;

    static const QString CYCLE_TRANSPORT_MAP_SERVER_A;
    static const QString CYCLE_TRANSPORT_MAP_SERVER_B;
    static const QString CYCLE_TRANSPORT_MAP_SERVER_C;

    int	standardMapServerIndex;
    int	cycleMapServerIndex;
    int	cycleTransportMapServerIndex;
};

#endif // QGVTILEREQUESTFACTORY_H
