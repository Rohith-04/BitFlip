#include "component.h"
#include "canvas.h"
#include "connectionpoint.h"
#include "wire.h"
#include <QGraphicsSceneMouseEvent>

Component::Component(QGraphicsItem *parent)
    : QObject(nullptr), QGraphicsItem(parent),
      m_canvas(nullptr)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Component::~Component()
{
    // Connection points are automatically deleted as they are child items
}

QVector2D Component::getPosition()
{
    return QVector2D(pos().x(), pos().y());
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Bring component to front when selected
    setZValue(1);
    QGraphicsItem::mousePressEvent(event);
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    
    // Update connection points when component moves
    updateConnectionPoints();
    
    // Update any connected wires
    for (auto* point : m_connectionPoints) {
        for (auto* wire : point->getConnectedWires()) {
            wire->updatePath();
        }
    }
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Reset z-value when released
    setZValue(0);
    QGraphicsItem::mouseReleaseEvent(event);
}

void Component::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // Default implementation - can be overridden by subclasses
    QGraphicsItem::mouseDoubleClickEvent(event);
}
