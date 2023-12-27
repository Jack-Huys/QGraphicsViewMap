#ifndef QGVDOWNLOADTILEREQUEST_H
#define QGVDOWNLOADTILEREQUEST_H

#include <QObject>
#include "QGVTileInfo.h"

class QGVDownloadTileRequest : public QObject
{
    Q_OBJECT
public:
    explicit QGVDownloadTileRequest();
    QGVDownloadTileRequest(QGVTileInfo tileInfo);
    ~QGVDownloadTileRequest();

    QGVTileInfo getTileInfo() const;
    void	 setTileInfo(QGVTileInfo tileInfo);

    QString	 getRequestUrl() const;
    void	 setRequestUrl(QString url);

private:
    QGVTileInfo tileInfo;
    QString  requestUrl;
};

#endif // QGVDOWNLOADTILEREQUEST_H
