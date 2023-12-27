#ifndef QGVBASEPOINTITEM_H
#define QGVBASEPOINTITEM_H

#include <QObject>
#include <QAbstractGraphicsShapeItem>


class QGVBasePointItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    enum PointType
    {
        Center = 0, // 中心点
        Edge,       // 边缘点（可拖动改变图形的形状、大小）
        Special     // 特殊功能点
    };

    QGVBasePointItem(QAbstractGraphicsShapeItem* parent, QPointF p, PointType type);

    QPointF getPoint() const;
    void setPoint(QPointF p);

 protected:

     virtual QRectF boundingRect() const override;

     virtual void paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget) override;
     virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

 private:
     QPointF m_point;    //点
     PointType m_type;   //点类型
};

#endif // QGVBASEPOINTITEM_H
