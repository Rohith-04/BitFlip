// wire.cpp
#include "wire.h"
#include "canvas.h"
#include <QPainter>
#include <QPen>

int Wire::count = 0;
std::vector<Wire *> Wire::listOfWires; //Declaring the static member


Wire::Wire(QGraphicsItem *parent)
    : QGraphicsPathItem(parent), color(Qt::black), isActive(false)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    m_wireData.startComponent = nullptr;
    m_wireData.endComponent = nullptr;
    m_wireData.state = false;
    count++;

    listOfWires.push_back(this);
}

void Wire::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Removing Wire";
        auto it = std::find(Wire::listOfWires.begin(), Wire::listOfWires.end(), this);

        if (it != Wire::listOfWires.end()) {
            Wire::listOfWires.erase(it);
        }
        if (scene()) {
            scene()->removeItem(this);
        }
        delete this;
    }
}

void Wire::addPoint(const QPointF &point)
{
    if (path.elementCount() == 0) {
        path.moveTo(point);
    } else {
        path.lineTo(point);
    }
    setPath(path);
}

void Wire::setColor(const QColor &newColor)
{
    color = newColor;
    update();
}

void Wire::setActive(bool active)
{
    isActive = active;
    update();
}

QRectF Wire::boundingRect() const{
    return path.boundingRect();
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void Wire::setState(bool state){
    isActive = state;
    update();

    if(m_wireData.endComponent){
        m_wireData.endComponent->handleLogic();
    }
}

/*
void Wire::logicHandling(){
    for(Wire *i : listOfWires){
        Component *startComp = i->m_wireData.startComponent;
        Component *endComp = i->m_wireData.endComponent;
    }
}
*/

bool Wire::getState() {
    return isActive;
}

