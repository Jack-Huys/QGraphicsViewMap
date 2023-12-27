#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "QGVBasePointItem.h"
#include "QGVBaseGraphicsItem.h"

QGVBasePointItem::QGVBasePointItem(QAbstractGraphicsShapeItem* parent, QPointF p, PointType type)
    : QAbstractGraphicsShapeItem(parent)
    , m_point(p)
    , m_type(type)
{
    this->setPos(m_point);
    this->setFlags(QGraphicsItem::ItemIsSelectable |
                       QGraphicsItem::ItemIsMovable |
                       QGraphicsItem::ItemIsFocusable);

    //设置鼠标类型
    switch (type)
    {
        case Center:
            this->setCursor(Qt::OpenHandCursor);
            break;
        case Edge:
            this->setCursor(Qt::PointingHandCursor);
            break;
        case Special:
            this->setCursor(Qt::PointingHandCursor);
            break;
        default: break;
    }
}

QPointF QGVBasePointItem::getPoint() const
{
    return m_point;

}

void QGVBasePointItem::setPoint(QPointF p)
{
    m_point = p;
}

QRectF QGVBasePointItem::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void QGVBasePointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    this->setPos(m_point);

    switch (m_type) {
    case Center:
        painter->drawEllipse(-4, -4, 8, 8);
        break;
    case Edge:
        painter->drawRect(QRectF(-4, -4, 8, 8));
        break;
    case Special:
        painter->drawRect(QRectF(-4, -4, 8, 8));
        break;
    default: break;
    }
}

void QGVBasePointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( event->buttons() == Qt::LeftButton )
    {
        qreal dx = event->scenePos().x() - event->lastScenePos().x();
        qreal dy = event->scenePos().y() - event->lastScenePos().y();

        QGVBaseGraphicsItem* item = static_cast<QGVBaseGraphicsItem *>(this->parentItem());
        ItemType itemType = item->getType();

        switch (m_type)
        {
        case Center: {
            item->moveBy(dx, dy);
            //this->scene()->update();
        } break;
        case Edge: {
            //略...
        } break;
        case Special: {
            //略...
        } break;
        default: break;
        }
    }
}
