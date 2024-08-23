#include "connectionpoint.h"

ConnectionPoint::ConnectionPoint(QGraphicsItem *parent) : QGraphicsEllipseItem(parent) {
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

    currentWire = nullptr;
}

float ConnectionPoint::getRadius(){
    return radius;
}

Wire* ConnectionPoint::getCurrentWire(){
    return currentWire;
}

void ConnectionPoint::setCurrentWire(Wire *wire){
    currentWire = wire;
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

void ConnectionPoint::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(!currentWire){
            currentWire = new Wire();
            currentWire->addPoint(scenePos());
            //view->addItem(currentWire);
        }
        else{
            currentWire->addPoint(scenePos());
            //currentWire->m_wireData.endComponent = this;
            currentWire = nullptr;
        }
    }
}

ConnectionPoint::~ConnectionPoint(){
    qDebug() << "ConnectionPoint is deleted";
}
