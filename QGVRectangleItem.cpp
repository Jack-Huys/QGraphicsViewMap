#include "QGVRectangleItem.h"
#include <QPainter>

QGVRectangleItem::QGVRectangleItem(qreal x, qreal y, qreal width, qreal height, ItemType type)
    :QGVBaseGraphicsItem(QPointF(x,y), QPointF(width/2,height/2), type)
{
    QGVBasePointItem *point = new QGVBasePointItem(this, m_edge, QGVBasePointItem::Edge);
    point->setParentItem(this);
//    m_pointList.append(point);
//    m_pointList.append(new QGVBasePointItem(this, m_center, QGVBasePointItem::Center));
//    m_pointList.setRandColor();
}

QRectF QGVRectangleItem::boundingRect() const
{
    return QRectF(m_center.x() - m_edge.x(), m_center.y() - m_edge.y(), m_edge.x() * 2, m_edge.y() * 2);
}

void QGVRectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());

    QRectF ret(m_center.x() - m_edge.x(), m_center.y() - m_edge.y(), m_edge.x() * 2, m_edge.y() * 2);
    painter->drawRect(ret);
}
