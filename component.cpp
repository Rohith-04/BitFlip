#include "component.h"

Component::Component(QGraphicsItem *parent)
    : QGraphicsItem(parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Component mouse press event";
    QGraphicsItem::mousePressEvent(event);
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Component mouse move event";
    QGraphicsItem::mouseMoveEvent(event);
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Component mouse release event";
    QGraphicsItem::mouseReleaseEvent(event);
}

void Component::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Component mouse double click event";
    QGraphicsItem::mouseDoubleClickEvent(event);
}
