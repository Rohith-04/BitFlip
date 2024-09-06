#include "canvas.h"
#include <QScrollBar>
#include <QDebug>
#include <QLineF>
#include <utility>
#include <limits>

Canvas::Canvas(QObject *parent) : QGraphicsScene(parent), view(nullptr){
    currentWire = nullptr;
    isDrawing = false;
}

void Canvas::addComponent(QGraphicsItem *comp) {
    if (!comp) {
        qDebug() << "Cannot add null component!";
        return;
    }
    addItem(comp);
}

void Canvas::addComponent(QGraphicsLineItem *line) {
    if (!line) {
        qDebug() << "Cannot add null line!";
        return;
    }
    addItem(line);
}

void Canvas::setView(QGraphicsView *view) {
    if (!view) {
        qDebug() << "Cannot set null view!";
        return;
    }
    this->view = view;
}

void Canvas::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (!view) {
        qDebug() << "View is not set!";
        return;
    }

    // Set the zoom factor
    double scaleFactor = 1.15;
    if (event->delta() < 0) {
        scaleFactor = 1.0 / scaleFactor;
    }

    // Get the current mouse position in scene coordinates
    //QPointF mouseScenePos = event->scenePos();

    // Calculate the new scale
    qreal currentScale = view->transform().m11(); // Get current horizontal scale
    qreal newScale = currentScale * scaleFactor;

    // Limit the scale to prevent extreme zooming
    if (newScale < 0.4 || newScale > 2.0){
        return;
    }

    // Set the transformation anchor to the cursor position
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Apply zoom
    view->scale(scaleFactor, scaleFactor);

    // Reset the transformation anchor
    view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void Canvas::startDrawing(){
    currentWire = new Wire();
    this->addItem(currentWire);
    isDrawing = true;

    qDebug() << isDrawing;
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isDrawing && currentWire) {
        qDebug() << "Started Drawing";
        QPointF currentPos = event->scenePos();
        currentWire->updatePath(currentPos); // Add a method in your Wire class to update the path
        update(); // Trigger a repaint
    }
    QGraphicsScene::mouseMoveEvent(event);
}

/*
void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(isDrawing && currentWire){
        currentWire = nullptr;
        isDrawing = false;
    }
}
*/
