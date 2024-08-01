#include "component.h"
#include "QVector2D"

Component::Component(ComponentType type, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_type(type) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Component mouse press event";
        QGraphicsItem::mousePressEvent(event);
    }
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        qDebug() << "Component mouse move event";
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Component mouse release event";
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

QVector2D Component::getPosition(){
    return(QVector2D(pos().x(), pos().y()));
}

ComponentType Component::getType() const{
    return m_type;
}
