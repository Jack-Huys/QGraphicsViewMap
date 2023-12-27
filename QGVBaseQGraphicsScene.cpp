#include "QGVBaseQGraphicsScene.h"
#include <QGraphicsSceneMouseEvent>

QGVBaseQGraphicsScene::QGVBaseQGraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    is_creating_BPolygon = false;
}

void QGVBaseQGraphicsScene::startCreate()
{
    is_creating_BPolygon = true;
    m_list.clear();
}

void QGVBaseQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (is_creating_BPolygon)
    {
        QPointF p(event->scenePos().x(), event->scenePos().y());

        switch ( event->buttons() )
        {
        case Qt::LeftButton:
        {
            m_list.push_back(p);
            emit updatePoint(p, m_list, false);
        }
        break;
        case Qt::RightButton:
        {
            if (m_list.size() >= 3)
            {
                emit updatePoint(p, m_list, true);
                emit createFinished();
                is_creating_BPolygon = false;
                m_list.clear();
            }
        }
        break;
        default: break;
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }

}
