#include "component.h"
#include "QVector2D"

Component::Component(QGraphicsItem *parent) : QGraphicsItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem::mousePressEvent(event);
    }
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        //qDebug() << "Component mouse move event";
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

QVector2D Component::getPosition(){
    return(QVector2D(pos().x(), pos().y()));
}


Component::~Component(){
    qDebug() << "Virtual Destructor is called";
}
