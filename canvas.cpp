#include "canvas.h"
#include <QScrollBar>
#include <QDebug>
#include <QLineF>
#include <utility>
#include <limits>

Canvas::Canvas(QObject *parent) : QGraphicsScene(parent), view(nullptr), isDrawingConnection(false), currentConnection(nullptr) {
    m_startComponent = nullptr;
    m_endComponent = nullptr;
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

void Canvas::repositionItems() {
    if (!view) {
        qDebug() << "View is not set!";
        return;
    }

    // Get the view's viewport size
    QSize viewportSize = view->viewport()->size();

    // Calculate the scene rectangle based on the viewport size
    QRectF newSceneRect(0, 0, viewportSize.width(), viewportSize.height());
    setSceneRect(newSceneRect);

    // Calculate margins and spacing
    qreal leftMargin = 50;
    qreal rightMargin = 50;
    qreal verticalSpacing = 20;

    // Position input items on the left
    qreal inputY = 50;  // Start with some top margin
    for (auto item = inputItems.begin(); item != inputItems.end(); item++ ) {
        if ((*item) == nullptr) {
            qDebug() << "Null input item detected!";
            continue;
        }
        (*item)->setPos(leftMargin, inputY);
        inputY += (*item)->boundingRect().height() + verticalSpacing;
    }

    // Position output items on the right
    qreal outputY = 50;  // Start with some top margin
    qreal outputX = newSceneRect.width() - rightMargin - (outputItems.isEmpty() ? 0 : outputItems.first()->boundingRect().width());
    for (auto item = outputItems.begin(); item != outputItems.end();item++) {
        if ((*item) == nullptr) {
            qDebug() << "Null output item detected!";
            continue;
        }
        (*item)->setPos(outputX, outputY);
        outputY += (*item)->boundingRect().height() + verticalSpacing;
    }

    // Update the scene rect to encompass all items
    QRectF itemsBoundingRect = this->itemsBoundingRect();
    setSceneRect(itemsBoundingRect.adjusted(-100, -100, 100, 100));  // Add some padding
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
    //view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}







