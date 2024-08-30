#include "connectionpoint.h"
#include "newproject.h"

ConnectionPoint::ConnectionPoint(QGraphicsItem *parent, NewProject *project) : QGraphicsEllipseItem(parent), m_project(project) {
    radius = 10.00f;
    setRect(0, 0, radius * 2, radius * 2);

    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(2);

    defaultColor = QColor(50, 52, 56, 255);
    hoverColor = QColor(103, 108, 115, 255);

    pen.setColor(defaultColor);
    setPen(pen);

    QBrush brush(defaultColor);
    setBrush(brush);

    setAcceptHoverEvents(true);
    qDebug() << "Connection Point is added";
    QObject::connect(this,&ConnectionPoint::ConnectionPointClicked, [this](){
        if(m_project == nullptr)
            qDebug() << "The project pointer is null";
        Canvas *canvas = m_project->getCanvas();
        qDebug() << "connected";
        if(canvas){
            canvas->startDrawing();
        }
    });
}

float ConnectionPoint::getRadius(){
    return radius;
}

void ConnectionPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    pen.setColor(hoverColor);
    setPen(pen);
    QBrush brush(hoverColor);
    setBrush(brush);
    update();

    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void ConnectionPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    pen.setColor(defaultColor);
    setPen(pen);
    QBrush brush(defaultColor);
    setBrush(brush);
    update();

    QGraphicsEllipseItem::hoverLeaveEvent(event);
}

void ConnectionPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "ConnectionPoint is clicked";
    emit ConnectionPointClicked();
    QGraphicsEllipseItem::mousePressEvent(event);
}

