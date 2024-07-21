#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "component.h"

class Canvas : public QGraphicsScene {
public:
    Canvas(QObject *parent = nullptr) : QGraphicsScene(parent) {}

    void addComponent(QGraphicsItem *comp);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Canvas mouse press event";
        QGraphicsScene::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Canvas mouse move event";
        QGraphicsScene::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Canvas mouse release event";
        QGraphicsScene::mouseReleaseEvent(event);
    }
};

#endif // CANVAS_H
