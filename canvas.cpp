#include "canvas.h"
#include "inputitem.h"
#include "outputitem.h"
#include <QScrollBar>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>

Canvas::Canvas(QObject *parent) : QGraphicsScene(parent), view(nullptr) {}

void Canvas::addComponent(QGraphicsItem *comp) {
    if (!comp) {
        qDebug() << "Cannot add null component!";
        return;
    }

    addItem(comp);

    if (InputItem *inputItem = dynamic_cast<InputItem*>(comp)) {
        inputItems.append(inputItem);
    } else if (OutputItem *outputItem = dynamic_cast<OutputItem*>(comp)) {
        outputItems.append(outputItem);
    }

    repositionItems();
}

void Canvas::setView(QGraphicsView *view) {
    this->view = view;
}


void Canvas::repositionItems() {
    if (!view) {
        qDebug() << "View is not set!";
        return;
    }

    qreal sceneWidth = sceneRect().width();

    // Position input items on the left
    qreal inputY = 0;
    for (auto item = inputItems.begin(); item != inputItems.end(); item++) {
        if (!*item) {
            qDebug() << "Null input item detected!";
            continue;
        }
        (*item)->setPos(10, inputY);
        inputY += (*item)->boundingRect().height() + 5;
    }

    // Position output items on the right
    qreal outputY = 0;
    qreal outputX = sceneWidth - (outputItems.isEmpty() ? 10 : outputItems.first()->boundingRect().width());
    for (auto item = outputItems.begin();item != outputItems.end(); item++) {
        if (!*item) {
            qDebug() << "Null output item detected!";
            continue;
        }
        (*item)->setPos(outputX, outputY);
        outputY += (*item)->boundingRect().height() + 5;
    }
}

void Canvas::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if (!view) {
        qDebug() << "View is not set!";
        return;
    }
    // Get the zoom factor
    float factor = 1.05;
    if (event->delta() < 0) {
        factor = 1 / factor;
    }

    // Calculate the zoom center
    QPointF zoomCenter = event->scenePos();

    // Store the current scroll bar positions
    int hScrollBarOldValue = view->horizontalScrollBar()->value();
    int vScrollBarOldValue = view->verticalScrollBar()->value();

    // Apply the zoom transformation
    view->scale(factor, factor);

    // Adjust the scroll bars to keep the zoom center stable
    QPointF delta = event->scenePos() - zoomCenter;
    view->horizontalScrollBar()->setValue(hScrollBarOldValue + delta.x());
    view->verticalScrollBar()->setValue(vScrollBarOldValue + delta.y());

}

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (view) {
            view->resetTransform();
            qDebug() << "Reset Zoom";
        } else {
            QGraphicsScene::mouseDoubleClickEvent(event);
        }
    }
}
