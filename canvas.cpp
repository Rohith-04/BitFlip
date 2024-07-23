#include "canvas.h"
#include <QScrollBar>
#include <QDebug>

Canvas::Canvas(QObject *parent)
    : QGraphicsScene(parent), view(nullptr), isPanning(false) {}

void Canvas::addComponent(QGraphicsItem *comp) {
    addItem(comp);
}

void Canvas::setView(QGraphicsView *view) {
    this->view = view;
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Canvas::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (view) {
        if (event->delta() > 0) {
            view->scale(1.1f, 1.1f);
            qDebug() << "Zooming in";
        } else {
            view->scale(1 / 1.1f, 1 / 1.1f);
            qDebug() << "Zooming out";
        }
    }
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (!item) {
            isPanning = true;
            lastPos = event->screenPos();
            if (view) {
                view->setCursor(Qt::ClosedHandCursor);
            }
            event->accept();
        } else {
            QGraphicsScene::mousePressEvent(event);
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isPanning) {
        QPoint delta = event->screenPos() - lastPos;
        if (view) {
            view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() - delta.x());
            view->verticalScrollBar()->setValue(view->verticalScrollBar()->value() - delta.y());
        }
        lastPos = event->screenPos();
        event->accept();
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (isPanning) {
        isPanning = false;
        if (view) {
            view->setCursor(Qt::ArrowCursor);
        }
        event->accept();
    } else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}


