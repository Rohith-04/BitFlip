#include "component.h"

Component::Component(QGraphicsItem *parent)
    : QGraphicsItem(parent) {
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

void Component::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Component mouse double click event";
    }
}
