#ifndef QGVMAPQGVIEW_H
#define QGVMAPQGVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>


//自定义地图视图类
class QGVMapQGView : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QPointF m_currentCenterPoint READ GetCenter WRITE SetCenter)
public:
    QGVMapQGView(QWidget* parent = nullptr);
    ~QGVMapQGView();

    //瓦片管理
    void addTile(QImage loadedImage, int x, int y, int imgSize);

    //标记管理
    void addMarker(int id, double x, double y, QImage image);
    void removeMarker(int id);
    void editMarker(int id, double x, double y);
    void clearAllMarker();

    //场景管理
    void clearScene();
    void centerScene(const QPointF& centerPoint);
    void isZoomEnable(bool);

signals:
    void visibleSceneChanged(QRectF visibleRect);
    void zoomUp();
    void zoomDown();

//public slots:
//    void zoomIn() { scale(1.2, 1.2); }
//    void zoomOut() { scale(1/1.2, 1/1.2); }

//    void rotateLeft() { rotate(-30); }
//    void rotateRight() { rotate(30); }

private:
    void initialize();                                     //初始化
    QPointF GetCenter() const;
    void SetCenter(const QPointF& centerPoint);

    //事件
    virtual void mousePressEvent(QMouseEvent* event) override final;
    virtual void mouseReleaseEvent(QMouseEvent* event) override final;
    virtual void mouseMoveEvent(QMouseEvent* event) override final;
    virtual void wheelEvent(QWheelEvent* event) override final;
    virtual void paintEvent(QPaintEvent* event) override final;


private:
    static const int MARKER_Z_LAYER;
    static const int TILE_Z_LAYER;
    static const int TILE_TEXT_Z_LAYER;
    static const int CROSSHAIR_Z_LAYER;

    QPointF m_currentCenterPoint;
    QPoint  m_lastPanPoint;

    QGraphicsScene* m_scene;                           //场景
    bool m_zoomEnable;                                 //是否可以变焦定位
    QHash<int, QGraphicsPixmapItem*>* m_markerHashMap; //地图数据图片Item

    QPropertyAnimation* m_animationScrolling;          //动画滚动
    QPropertyAnimation* m_animationScale;              //动画缩放

};

#endif // QGVMAPQGVIEW_H
