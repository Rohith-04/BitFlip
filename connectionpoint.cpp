#include "canvas.h"
#include "connectionpoint.h"
#include "component.h"
#include "wire.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>

ConnectionPoint::ConnectionPoint(Component* parent, Type type, int index)
    : QGraphicsEllipseItem(-5, -5, 10, 10, parent),
      m_parentComponent(parent),
      m_type(type),
      m_index(index),
      m_value(false)
{
    // Set appearance
    setBrush(QBrush(Qt::red));
    setPen(QPen(Qt::black, 1));
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    
    // Input points are typically on the left, output on the right
    if (type == Input) {
        setBrush(QBrush(Qt::blue));
    } else {
        setBrush(QBrush(Qt::red));
    }
}

ConnectionPoint::~ConnectionPoint()
{
    // Disconnect all wires
    for (Wire* wire : m_connectedWires) {
        wire->disconnect();
    }
}

void ConnectionPoint::addWire(Wire* wire)
{
    if (!m_connectedWires.contains(wire)) {
        m_connectedWires.append(wire);
    }
}

void ConnectionPoint::removeWire(Wire* wire)
{
    m_connectedWires.removeAll(wire);
}

void ConnectionPoint::setValue(bool value)
{
    if (m_value != value) {
        m_value = value;
        
        // Update visual appearance
        setBrush(QBrush(m_value ? Qt::green : (m_type == Input ? Qt::blue : Qt::red)));
        
        // Propagate value change if this is an output
        if (m_type == Output) {
            emit valueChanged(m_value);
            
            // Update connected wires
            for (Wire* wire : m_connectedWires) {
                wire->propagateValue(m_value);
            }
        }
    }
}

void ConnectionPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Get the canvas
        Canvas* canvas = dynamic_cast<Canvas*>(scene());
        if (canvas) {
            canvas->startWireCreation(this);
            event->accept();
            return;
        }
    }
    QGraphicsEllipseItem::mousePressEvent(event);
}

void ConnectionPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Complete wire creation
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}
