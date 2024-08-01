// connection.cpp
#include "connection.h"
#include <QPainter>
#include <QPen>

int Connection::count = 0;

Connection::Connection(QGraphicsItem *parent)
    : QGraphicsPathItem(parent), color(Qt::black), isActive(false)
{
    //setZValue(-1);
    m_connectionData.startComponent = nullptr;
    m_connectionData.endComponent = nullptr;
    count++;
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

void setState(bool state){}
