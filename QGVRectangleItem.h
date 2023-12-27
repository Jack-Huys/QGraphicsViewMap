#ifndef QGVRECTANGLEITEM_H
#define QGVRECTANGLEITEM_H

#include "QGVBaseGraphicsItem.h"
#include "QGVBasePointItem.h"

class QGVRectangleItem : public QGVBaseGraphicsItem
{
public:
    QGVRectangleItem(qreal x, qreal y, qreal width, qreal height, ItemType type);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

//private:
//    QGVBasePointItemList m_pointList;
};

#endif // QGVRECTANGLEITEM_H
