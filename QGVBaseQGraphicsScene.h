#ifndef QGVBASEQGRAPHICSSCENE_H
#define QGVBASEQGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

//场景类
class QGVBaseQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    QGVBaseQGraphicsScene(QObject *parent = nullptr);

    void startCreate();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void updatePoint(QPointF p, QList<QPointF> list, bool isCenter);
    void createFinished();

protected:
    QList<QPointF> m_list;
    bool is_creating_BPolygon;  //是否创建多边形
};

#endif // QGVBASEQGRAPHICSSCENE_H
