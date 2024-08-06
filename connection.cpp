// connection.cpp
#include "connection.h"
#include "canvas.h"
#include <QPainter>
#include <QPen>

int Connection::count = 0;
QVector<Connection *> Connection::listOfConnections; //Declaring the static members


Connection::Connection(QGraphicsItem *parent)
    : QGraphicsPathItem(parent), color(Qt::black), isActive(false)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    //setZValue(-1);
    m_connectionData.startComponent = nullptr;
    m_connectionData.endComponent = nullptr;
    count++;

    listOfConnections.append(this);
}

void Connection::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        qDebug() << "Removing Connection";
        if(scene()){
            scene()->removeItem(this);
        }
    delete this;
    }
}
void Connection::addPoint(const QPointF &point)
{
    if (path.elementCount() == 0) {
        path.moveTo(point);
    } else {
        path.lineTo(point);
    }
    setPath(path);
}

void Connection::setColor(const QColor &newColor)
{
    color = newColor;
    update();
}

void Connection::setActive(bool active)
{
    isActive = active;
    update();
}

QRectF Connection::boundingRect() const{
    return path.boundingRect();
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(isActive ? color.lighter(150) : color);
    pen.setWidth(10);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawPath(path);
}

void Connection::setState(bool state){
    isActive = state;
    update();

    if(m_connectionData.endComponent){
        m_connectionData.endComponent->handleLogic();
    }
}

/*
void Connection::logicHandling(){
    for(Connection *i : listOfConnections){
        Component *startComp = i->m_connectionData.startComponent;
        Component *endComp = i->m_connectionData.endComponent;
    }
}
*/

bool Connection::getState() {
    return isActive;  // Implement the method
}

