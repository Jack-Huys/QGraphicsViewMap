#ifndef QGVBASEGRAPHICSITEM_H
#define QGVBASEGRAPHICSITEM_H

#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QPen>

#include "QGVBasePointItemList.h"

//Item类型
enum ItemType {
    Circle = 0,         // 圆
    Ellipse,            // 椭圆
    Concentric_Circle,  // 同心圆
    Pie,                // 饼
    Chord,              // 和弦
    Rectangle,          // 矩形
    Square,             // 正方形
    Polygon,            // 多边形
    Round_End_Rectangle,// 圆端矩形
    Rounded_Rectangle   // 圆角矩形
};


//图元基类
class QGVBaseGraphicsItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:

    QPointF getCenter() const{ return m_center; }
    void setCenter(QPointF p) { m_center = p; }

    QPointF getEdge() const{ return m_edge; }
    void setEdge(QPointF p) { m_edge = p; }

    ItemType getType() const{ return m_type; }

protected:
    QGVBaseGraphicsItem(QPointF center, QPointF edge, ItemType type);

    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

protected:
    QPointF m_center;
    QPointF m_edge;
    ItemType m_type;
    QGVBasePointItemList m_pointList;

    QPen m_pen_isSelected;
    QPen m_pen_noSelected;

};

#endif // QGVBASEGRAPHICSITEM_H
