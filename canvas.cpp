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

    if (InputItem *inputItem = dynamic_cast<InputItem*>(comp)) {
        inputItems.append(inputItem);
    } else if (OutputItem *outputItem = dynamic_cast<OutputItem*>(comp)) {
        outputItems.append(outputItem);
    }

    repositionItems();
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
    repositionItems();

    // Reset the transformation anchor
    //view->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

/*
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
*/

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        qDebug() << "Starting the drawing";
        auto result = getNearestConnectionPoint(event->scenePos());
        QPointF connectionPoint = result.first;
        Component *component = result.second;
        if (component) {
            isDrawingConnection = true;
            currentConnection = new Connection();
            addItem(currentConnection);
            lastPoint = connectionPoint;
            currentConnection->addPoint(lastPoint);
            m_startComponent = component;
            lastDirection = Qt::Horizontal;  // Initialize with a default direction
            currentConnection->m_connectionData.startPosition = result.first; // Finalising the first connection point
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isDrawingConnection && currentConnection) {
        QPointF newPoint = event->scenePos();
        QPointF adjustedPoint;

        // Determine the dominant direction (horizontal or vertical)
        qreal dx = qAbs(newPoint.x() - lastPoint.x());
        qreal dy = qAbs(newPoint.y() - lastPoint.y());

        if (dx > dy) {
            // Draw horizontally
            adjustedPoint = QPointF(newPoint.x(), lastPoint.y());
        } else {
            // Draw vertically
            adjustedPoint = QPointF(lastPoint.x(), newPoint.y());
        }

        // Only add the point if it's sufficiently far from the last point
        if (QLineF(lastPoint, adjustedPoint).length() > 30.0) {
            currentConnection->addPoint(adjustedPoint);
            lastPoint = adjustedPoint;
            update();  // Ensure the scene is updated
        }
        event->accept();
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton && isDrawingConnection) {
        qDebug() << "Finished Drawing";
        auto result = getNearestConnectionPoint(event->scenePos());
        QPointF endPoint = result.first;
        m_endComponent = result.second;

        if (m_endComponent && m_endComponent != m_startComponent) {
            // Add the final segment based on the last direction
            qreal dx = qAbs(endPoint.x() - lastPoint.x());
            qreal dy = qAbs(endPoint.y() - lastPoint.y());

            if (dx > dy) {
                // Finish with a horizontal line
                currentConnection->addPoint(QPointF(endPoint.x(), lastPoint.y()));
            } else {
                // Finish with a vertical line
                currentConnection->addPoint(QPointF(lastPoint.x(), endPoint.y()));
            }
            currentConnection->addPoint(endPoint);

            // Set the connection as active once completed
            currentConnection->setActive(true);
        }
        else {
            // Remove the incomplete connection if it doesn't end at a valid component
            removeItem(currentConnection);
            delete currentConnection;
        }
        if(currentConnection){
        currentConnection->m_connectionData.startComponent = m_startComponent; // Storing the start component
        currentConnection->m_connectionData.endComponent = m_endComponent; // Storing the end component
        currentConnection->m_connectionData.endPosition = result.first; //Finalising last connection position
        }

        //qDebug() << currentConnection->m_connectionData.startComponent->getType();
        //qDebug() << currentConnection->m_connectionData.endComponent->getType();
        //Resetting the things
        isDrawingConnection = false;
        currentConnection = nullptr;
        m_startComponent = nullptr;
        m_endComponent = nullptr;
        update();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

std::pair<QPointF, Component*> Canvas::getNearestConnectionPoint(const QPointF &scenePos) {
    const qreal MAX_DISTANCE = 40.0;  // Temporarily increased for testing
    QPointF nearest;
    Component *nearComponent = nullptr;
    qreal minDistance = std::numeric_limits<qreal>::max();

    //qDebug() << "Scene position:" << scenePos;
    //qDebug() << "Number of items in scene:" << items().count();

    for (QGraphicsItem *item : items()) {
        //qDebug() << "Checking item type:" << item->type();

        Component *component = dynamic_cast<Component*>(item);
        if (component) {
            //qDebug() << "  Found component:" << component;
            QList<QPointF> connectionPoints = component->getConnectionPoints();
            //qDebug() << "  Number of connection points:" << connectionPoints.size();

            for (const QPointF &point : connectionPoints) {
                QPointF scenePoint = component->mapToScene(point);
                qreal distance = QLineF(scenePos, scenePoint).length();
                //qDebug() << "    Connection point:" << scenePoint << "Distance:" << distance;

                if (distance < minDistance && distance < MAX_DISTANCE) {
                    minDistance = distance;
                    nearest = scenePoint;
                    nearComponent = component;
                }
            }
        } else {
            //qDebug() << "  Item is not a Component";
        }
    }

    return std::make_pair(nearest, nearComponent);
}

