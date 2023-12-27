#include "QGVMapQGView.h"
#include <QGLWidget>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

const int QGVMapQGView::MARKER_Z_LAYER = 10;
const int QGVMapQGView::TILE_Z_LAYER = 0;
const int QGVMapQGView::TILE_TEXT_Z_LAYER = 1;
const int QGVMapQGView::CROSSHAIR_Z_LAYER = 5;

QGVMapQGView::QGVMapQGView(QWidget* parent)
    :QGraphicsView(parent)
{
    this->setParent(parent);
    initialize();
}

QGVMapQGView::~QGVMapQGView()
{

}

void QGVMapQGView::addTile(QImage loadedImage, int x, int y, int imgSize)
{
    //从照片格式转换成QPixmap
    QPixmap displayedImage = QPixmap::fromImage(loadedImage);
    QGraphicsPixmapItem* displayedItem = new QGraphicsPixmapItem(displayedImage);
    this->m_scene->addItem(displayedItem);
    displayedItem->setPos(x*imgSize,y*imgSize);
    displayedItem->setZValue(TILE_Z_LAYER);

    QRectF bound = this->m_scene->itemsBoundingRect();
    QRectF enlargedBound = QRectF(bound.x() - 100, bound.y() - 100, bound.width() + 200, bound.height() + 200);
    setSceneRect(enlargedBound);

}

void QGVMapQGView::addMarker(int id, double x, double y, QImage image)
{
    if (!this->m_markerHashMap->contains(id))
    {
        // Convert from QImage to QPixmap
        QPixmap pixmap = QPixmap::fromImage(image);
        // Add Pixmap to the Scene
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        this->m_scene->addItem(item);
        item->setPos(x,y);
        item->setZValue(1);
        item->setTransformationMode(Qt::SmoothTransformation);
        this->m_markerHashMap->insert(id, item);
    }

}

void QGVMapQGView::removeMarker(int id)
{
    if(this->m_markerHashMap->contains(id))
    {
        QGraphicsPixmapItem* item = this->m_markerHashMap->value(id);
        this->m_scene->removeItem(item);
        delete item;
        item = nullptr;
        this->m_markerHashMap->remove(id);
    }

}

void QGVMapQGView::editMarker(int id, double x, double y)
{
    if(this->m_markerHashMap->contains(id))
    {
        QGraphicsPixmapItem* item = this->m_markerHashMap->value(id);
        item->setPos(x,y);
    }

}

void QGVMapQGView::clearAllMarker()
{
    QHash<int, QGraphicsPixmapItem*>::const_iterator i;
    for (i = this->m_markerHashMap->constBegin(); i != this->m_markerHashMap->constEnd(); ++i)
    {
        QGraphicsPixmapItem* item = this->m_markerHashMap->value(i.key());
        this->m_scene->removeItem(item);
        delete item;
        item = nullptr;
    }
    this->m_markerHashMap->clear();

}

void QGVMapQGView::clearScene()
{
    clearAllMarker();
    this->m_scene->clear();
}

void QGVMapQGView::centerScene(const QPointF &centerPoint)
{
    centerOn(centerPoint);

    // Invisible crosshair... can be used for debug if we draw diff color
    QGraphicsLineItem* item1 = new QGraphicsLineItem(0, centerPoint.y(), INT_MAX, centerPoint.y());
    item1->setPen(QPen(QColor(0, 0, 0, 0)));
    item1->setZValue(10);

    QGraphicsLineItem* item2 = new QGraphicsLineItem(centerPoint.x(), 0, centerPoint.x(), INT_MAX);
    item2->setPen(QPen(QColor(0, 0, 0, 0)));
    item2->setZValue(10);

    m_scene->addItem(item1);
    m_scene->addItem(item2);

    m_currentCenterPoint = centerPoint;
    SetCenter(centerPoint);
}

void QGVMapQGView::isZoomEnable(bool)
{
    m_zoomEnable = true;
}

void QGVMapQGView::initialize()
{
    this->setupViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->update();

    //场景初始化
    this->m_scene = new QGraphicsScene(this);
    this->setScene(m_scene);
    this->setBackgroundBrush(QBrush(QColor(20,20,20), Qt::SolidPattern));
    this->setCursor(Qt::OpenHandCursor);

    //设置垂直、水平滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setFrameStyle(QFrame::Box);
    this->setMouseTracking(true);

    this->m_markerHashMap = new QHash<int, QGraphicsPixmapItem*>();
    this->m_zoomEnable = false;

    this->m_animationScrolling = new QPropertyAnimation(this,"CurrentCenterPoint");
    this->m_animationScrolling->setDuration(600);
    this->m_animationScrolling->setEasingCurve(QEasingCurve::OutQuad);

}

QPointF QGVMapQGView::GetCenter() const
{
    return m_currentCenterPoint;
}

void QGVMapQGView::SetCenter(const QPointF &centerPoint)
{
    m_currentCenterPoint = centerPoint;
    centerOn(m_currentCenterPoint);

    QPointF topLeft = mapToScene (0, 0);
    QPointF bottomRight = mapToScene(this->width(), this->height());

    QRectF rectangle(topLeft, bottomRight);
    emit visibleSceneChanged(rectangle);
}

void QGVMapQGView::mousePressEvent(QMouseEvent *event)
{
    m_lastPanPoint = event->pos();
    setCursor(Qt::ClosedHandCursor);

    // stop the inertial animation
    m_animationScrolling->stop();
    m_animationScrolling->setEndValue(GetCenter());
}

void QGVMapQGView::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);

    if(!m_lastPanPoint.isNull())
    {
        //Get how much we panned
        QPointF delta = mapToScene(m_lastPanPoint) - mapToScene(event->pos());
        m_lastPanPoint = event->pos();
    }
    m_lastPanPoint = QPoint();
}

void QGVMapQGView::mouseMoveEvent(QMouseEvent *event)
{
    float latOffset = 0;
    float lonOffset = 0;

    if(!m_lastPanPoint.isNull())
    {
        // Get how much we panned
        QPointF delta = mapToScene(m_lastPanPoint) - mapToScene(event->pos());
        m_lastPanPoint = event->pos();

        setSceneRect(sceneRect().x() + delta.x(), sceneRect().y() + delta.y(), sceneRect().width(), sceneRect().height());

        // Update the center ie. do the pan
        SetCenter(GetCenter() + delta);

        // Set animation properties
        m_animationScrolling->setDuration(200 + delta.manhattanLength() * 3);
        if (m_animationScrolling->duration() > 1000)
        {
            m_animationScrolling->setDuration(1000);
        }

        // Set animation end
        m_animationScrolling->setEndValue(GetCenter()+delta*14);
    }
}

void QGVMapQGView::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (delta > 0)
    {
        emit zoomDown();
    }
    else if (delta < 0)
    {
        emit zoomUp();
    }

    if (m_zoomEnable)
    {
        static float totalScale = 1;
        m_animationScrolling->stop();
        m_animationScrolling->setEndValue(GetCenter());

        //Get the position of the mouse before scaling, in scene coords
        QPointF pointBeforeScale(mapToScene(event->pos()));

        //Get the original screen centerpoint
        QPointF screenCenter = GetCenter();

        //Get the rectangle of the visible area in scene coords
        QRectF visibleArea = mapToScene(rect()).boundingRect();

        //Get the scene area
        QRectF sceneBounds = sceneRect();

        if(event->orientation() == 1)
        {
            delta = 0;
        }

        double scaleFactor;
        if(delta > 0)
        {
            scaleFactor = 1 + (delta / 2500.0);
        }
        else
        {
            scaleFactor = 1 + (delta / 3000.0);
        }

        if(scaleFactor < 0)
        {
            scaleFactor = 1;
        }

        int heightFactor = visibleArea.height()/m_scene->itemsBoundingRect().height();
        int widthFactor  = visibleArea.width() /m_scene->itemsBoundingRect().width();

        if( ((visibleArea.height() < m_scene->itemsBoundingRect().height() || visibleArea.width() < m_scene->itemsBoundingRect().width()))
            && delta < 0)
        {
            scale(scaleFactor, scaleFactor);
        }
        else if(visibleArea.height() > 100 && delta > 0)
        {
            scale(scaleFactor, scaleFactor);
        }
        else
        {
            scale(scaleFactor, scaleFactor);
        }

        QPointF pointAfterScale(mapToScene(event->pos()));
        QPointF offset = pointBeforeScale - pointAfterScale;
        QPointF newCenter = screenCenter + offset;
        SetCenter(newCenter);
        update();
    }
}

void QGVMapQGView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}


