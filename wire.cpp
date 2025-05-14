#include "wire.h"
#include "connectionpoint.h"
#include "component.h"
#include <QPainterPath>
#include <QPen>

Wire::Wire(ConnectionPoint* startPoint, ConnectionPoint* endPoint, QGraphicsItem* parent)
    : QGraphicsPathItem(parent),
      m_startPoint(nullptr),
      m_endPoint(nullptr),
      m_value(false)
{
    setPen(QPen(Qt::black, 2));
    setZValue(-1); // Ensure wires are below components
    
    if (startPoint) {
        setStartPoint(startPoint);
    }
    
    if (endPoint) {
        setEndPoint(endPoint);
    }
}

Wire::~Wire()
{
    disconnect();
}

void Wire::setStartPoint(ConnectionPoint* point)
{
    // Disconnect from old point if exists
    if (m_startPoint) {
        m_startPoint->removeWire(this);
        // Use QObject::disconnect instead of just disconnect
        QObject::disconnect(m_startPoint, &ConnectionPoint::valueChanged, this, &Wire::onStartPointValueChanged);
    }

    m_startPoint = point;

    if (m_startPoint) {
        m_startPoint->addWire(this);
        connect(m_startPoint, &ConnectionPoint::valueChanged, this, &Wire::onStartPointValueChanged);

        // Update wire value based on start point
        if (m_startPoint->getType() == ConnectionPoint::Output) {
            propagateValue(m_startPoint->getValue());
        }
    }

    updatePath();
}


void Wire::setEndPoint(ConnectionPoint* point)
{
    // Disconnect from old point if exists
    if (m_endPoint) {
        m_endPoint->removeWire(this);
    }
    
    m_endPoint = point;
    
    if (m_endPoint) {
        m_endPoint->addWire(this);
        
        // Update end point value if wire already has a value
        if (m_startPoint && m_startPoint->getType() == ConnectionPoint::Output) {
            propagateValue(m_startPoint->getValue());
        }
    }
    
    updatePath();
}

void Wire::updatePath()
{
    if (m_startPoint && m_endPoint) {
        QPointF startPos = m_startPoint->scenePos();
        QPointF endPos = m_endPoint->scenePos();
        
        QPainterPath path;
        path.moveTo(startPos);
        
        // Create a nice curved path
        qreal dx = endPos.x() - startPos.x();
        path.cubicTo(
            startPos.x() + dx * 0.5, startPos.y(),
            endPos.x() - dx * 0.5, endPos.y(),
            endPos.x(), endPos.y()
        );
        
        setPath(path);
    }
}

void Wire::disconnect()
{
    if (m_startPoint) {
        m_startPoint->removeWire(this);
        QObject::disconnect(m_startPoint, &ConnectionPoint::valueChanged, this, &Wire::onStartPointValueChanged);
        m_startPoint = nullptr;
    }

    if (m_endPoint) {
        m_endPoint->removeWire(this);
        m_endPoint = nullptr;
    }
}
void Wire::propagateValue(bool value)
{
    if (m_value != value) {
        m_value = value;
        updateAppearance();
        
        // Propagate to end point if it's an input
        if (m_endPoint && m_endPoint->getType() == ConnectionPoint::Input) {
            m_endPoint->setValue(value);
        }
    }
}
void Wire::onStartPointValueChanged(bool value)
{
    propagateValue(value);
}

void Wire::updateAppearance()
{
    // Change color based on signal value
    setPen(QPen(m_value ? Qt::green : Qt::black, 2));
}
