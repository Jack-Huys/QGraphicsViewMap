#ifndef QGVTILEONLINELOADER_H
#define QGVTILEONLINELOADER_H

#include <QObject>
#include <QNetworkAccessManager>

#include "QGVTileInfo.h"
#include "QGVTile.h"
#include "QGVTileRequestFactory.h"
class QGVTileRequestFactory;
class QGVTileOnlineLoader : public QObject
{
    Q_OBJECT

    public:
        QGVTileOnlineLoader();
        ~QGVTileOnlineLoader();
        void loadTile(QGVTileInfo info);

    private:
        QNetworkAccessManager*	networkAccesManager;
        QGVTileRequestFactory  tileRequestFactory;
        QString                 requestUserAgent;

    private slots:
        void networkReplyReady(QNetworkReply* reply);

    signals:
        void onlineTileLoaded(QGVTile tile);
};

#endif // QGVTILEONLINELOADER_H
