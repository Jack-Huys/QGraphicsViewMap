#include "QGVTileRequestFactory.h"

#if 1
const QString QGVTileRequestFactory::STANDARD_MAP_SERVER_A = "http://a.tile.openstreetmap.org/%1/%2/%3.png";
const QString QGVTileRequestFactory::STANDARD_MAP_SERVER_B = "http://b.tile.openstreetmap.org/%1/%2/%3.png";
const QString QGVTileRequestFactory::STANDARD_MAP_SERVER_C = "http://c.tile.openstreetmap.org/%1/%2/%3.png";

const QString QGVTileRequestFactory::CYCLE_MAP_SERVER_A = "http://a.tile.opencyclemap.org/cycle/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_MAP_SERVER_B = "http://b.tile.opencyclemap.org/cycle/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_MAP_SERVER_C = "http://c.tile.opencyclemap.org/cycle/%1/%2/%3.png";

const QString QGVTileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_A = "http://a.tile2.opencyclemap.org/transport/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_B = "http://b.tile2.opencyclemap.org/transport/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_C = "http://c.tile2.opencyclemap.org/transport/%1/%2/%3.png";
#else
const QString QGVTileRequestFactory::STANDARD_MAP_SERVER_A = "http://a.tile.openstreetmap.cn/%1/%2/%3.png";
const QString QGVTileRequestFactory::STANDARD_MAP_SERVER_B = "http://b.tile.openstreetmap.cn/%1/%2/%3.png";
const QString QGVTileRequestFactory::STANDARD_MAP_SERVER_C = "http://c.tile.openstreetmap.cn/%1/%2/%3.png";

const QString QGVTileRequestFactory::CYCLE_MAP_SERVER_A = "http://a.tile.opencyclemap.cn/cycle/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_MAP_SERVER_B = "http://b.tile.opencyclemap.cn/cycle/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_MAP_SERVER_C = "http://c.tile.opencyclemap.cn/cycle/%1/%2/%3.png";

const QString QGVTileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_A = "http://a.tile2.opencyclemap.cn/transport/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_B = "http://b.tile2.opencyclemap.cn/transport/%1/%2/%3.png";
const QString QGVTileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_C = "http://c.tile2.opencyclemap.cn/transport/%1/%2/%3.png";
#endif


QGVTileRequestFactory::QGVTileRequestFactory()
{

}

QGVTileRequestFactory::~QGVTileRequestFactory()
{

}

QGVDownloadTileRequest *QGVTileRequestFactory::createTileRequest(QGVTileInfo info)
{
    QString urlString;

    TileTypeEnum type = info.getTileType();

    switch(type)
    {
        case STANDARD:
            if (standardMapServerIndex % 3 == 0)
            {
                urlString = STANDARD_MAP_SERVER_A;
            }
            else if (standardMapServerIndex % 3 == 1)
            {
                urlString = STANDARD_MAP_SERVER_B;
            }
            else
            {
                urlString = STANDARD_MAP_SERVER_C;
            }
            standardMapServerIndex++;
            break;
        case CYCLE:
            if (cycleMapServerIndex % 3 == 0)
            {
                urlString = CYCLE_MAP_SERVER_A;
            }
            else if (cycleMapServerIndex % 3 == 1)
            {
                urlString = CYCLE_MAP_SERVER_B;
            }
            else
            {
                urlString = CYCLE_MAP_SERVER_C;
            }
            cycleMapServerIndex++;
            break;
        case CYCLE_TRANSPORT:
            if (cycleTransportMapServerIndex % 3 == 0)
            {
                urlString = CYCLE_TRANSPORT_MAP_SERVER_A;
            }
            else if (cycleTransportMapServerIndex % 3 == 1)
            {
                urlString = CYCLE_TRANSPORT_MAP_SERVER_B;
            }
            else
            {
                urlString = CYCLE_TRANSPORT_MAP_SERVER_C;
            }
            cycleTransportMapServerIndex++;
            break;
        default:
            break;
    }

    urlString = urlString.arg(info.getZoom()).arg(info.getX()).arg(info.getY());

    QGVDownloadTileRequest* request = new QGVDownloadTileRequest(info);
    request->setRequestUrl(urlString);

    // Return created request
    return request;
}
