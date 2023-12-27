#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "QGVMapMarker.h"


#define M_PI 3.1415926

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class QGVMapQGView;
class QGVMapTileManager;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void standardButtonPressed();
    void cycleButtonPressed();
    void cycleTransportButtonPressed();
    void zoomUpButtonPressed();
    void zoomDownButtonPressed();

private:
    virtual void wheelEvent(QWheelEvent* event);

private:
    Ui::Widget *ui;

private:
    QGVMapMarker planeMarker;
    QGVMapTileManager* m_tileManager;
    QGVMapQGView* m_mapView;

    QPushButton* m_standardButton;
    QPushButton* m_cycleButton;
    QPushButton* m_cycleTransportButton;
    QPushButton* m_zoomUpButton;
    QPushButton* m_zoomDownButton;
};
#endif // WIDGET_H
