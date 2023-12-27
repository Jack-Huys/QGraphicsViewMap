#include "QGVDownloadTileRequest.h"

QGVDownloadTileRequest::QGVDownloadTileRequest()
{

}

QGVDownloadTileRequest::QGVDownloadTileRequest(QGVTileInfo tileInfo)
{
    this->tileInfo = tileInfo;
}

QGVDownloadTileRequest::~QGVDownloadTileRequest()
{

}

QGVTileInfo QGVDownloadTileRequest::getTileInfo() const
{
    return tileInfo;
}

void QGVDownloadTileRequest::setTileInfo(QGVTileInfo tileInfo)
{
    this->tileInfo = tileInfo;
}

QString QGVDownloadTileRequest::getRequestUrl() const
{
    return requestUrl;
}

void QGVDownloadTileRequest::setRequestUrl(QString url)
{
    this->requestUrl = url;
}
