#include "widget.h"
#include "ui_widget.h"
#include "QGVMapQGView.h"
#include "QGVMapTileManager.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    m_mapView = new QGVMapQGView(this);
    vBoxLayout->addWidget(m_mapView);
    //setCentralWidget(this);
    this->setLayout(vBoxLayout);
    this->resize(800,600);

    m_standardButton = new QPushButton("Standard");
    m_standardButton->setParent(m_mapView);
    m_standardButton->move(10, 20);
    QObject::connect
    (
        m_standardButton,		SIGNAL(pressed()),
        this,				SLOT(standardButtonPressed())
    );

    m_cycleButton = new QPushButton("Cycle");
    m_cycleButton->setParent(m_mapView);
    m_cycleButton->move(10, 50);
    QObject::connect
    (
        m_cycleButton,		SIGNAL(pressed()),
        this,				SLOT(cycleButtonPressed())
    );

    m_cycleTransportButton = new QPushButton("Cycle Transport");
    m_cycleTransportButton->setParent(m_mapView);
    m_cycleTransportButton->move(10, 80);
    QObject::connect
    (
        m_cycleTransportButton,	SIGNAL(pressed()),
        this,					SLOT(cycleTransportButtonPressed())
    );

    m_zoomUpButton = new QPushButton("Zoom Up");
    m_zoomUpButton->setParent(m_mapView);
    m_zoomUpButton->move(10, 110);
    QObject::connect
    (
        m_zoomUpButton,			SIGNAL(pressed()),
        this,					SLOT(zoomUpButtonPressed())
    );

    m_zoomDownButton = new QPushButton("Zoom Down");
    m_zoomDownButton->setParent(m_mapView);
    m_zoomDownButton->move(10, 140);
    QObject::connect
    (
        m_zoomDownButton,			SIGNAL(pressed()),
        this,					SLOT(zoomDownButtonPressed())
    );


    this->m_tileManager = new QGVMapTileManager(m_mapView);

    double latitude1 = 104.06573;
    double longitude1 = 30.659462;

    double latitude2 = 103.723851;
    double longitude2 = 34.659462;
//    double latitude1 = 45.713851;
//    double longitude1 = -74.07692;

//    double latitude2 = 45.420624;
//    double longitude2 = -73.427353;
    int zoomFactor = 6;

    this->m_tileManager->fovChanged(latitude1, longitude1, latitude2, longitude2, zoomFactor, true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::standardButtonPressed()
{
    m_tileManager->changeTileType(STANDARD);
}

void Widget::cycleButtonPressed()
{
    m_tileManager->changeTileType(CYCLE);
}

void Widget::cycleTransportButtonPressed()
{
    m_tileManager->changeTileType(CYCLE_TRANSPORT);
}

void Widget::zoomUpButtonPressed()
{
    m_tileManager->zoomUp();
}

void Widget::zoomDownButtonPressed()
{
    m_tileManager->zoomDown();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (delta > 0)
    {
        m_tileManager->zoomDown();
    }
    else if (delta < 0)
    {
        m_tileManager->zoomDown();
    }
}

