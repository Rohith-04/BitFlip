#include "canvas.h"
#include "component.h"
#include "connectionpoint.h"
#include "wire.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Canvas::Canvas(QObject *parent)
    : QGraphicsScene(parent),
      m_creatingWire(false),
      m_wireStartPoint(nullptr),
      m_tempWire(nullptr),
      m_view(nullptr)
{
    // Set a reasonable scene size
    setSceneRect(0, 0, 800, 600);
    
    // Set a background color
    setBackgroundBrush(QBrush(Qt::lightGray));
}

Canvas::~Canvas()
{
    // Clean up components and wires
    for (auto* component : m_components) {
        delete component;
    }
    
    for (auto* wire : m_wires) {
        delete wire;
    }
}

void Canvas::addComponent(Component* component)
{
    if (!m_components.contains(component)) {
        m_components.append(component);
        addItem(component);
    }
}

void Canvas::removeComponent(Component* component)
{
    if (m_components.contains(component)) {
        m_components.removeAll(component);
        removeItem(component);
        delete component;
    }
}

void Canvas::startWireCreation(ConnectionPoint* startPoint)
{
    if (!m_creatingWire && startPoint) {
        m_creatingWire = true;
        m_wireStartPoint = startPoint;
        
        // Create a temporary wire
        m_tempWire = new Wire(nullptr, nullptr);
        addItem(m_tempWire);
        
        // Set initial path
        QPainterPath path;
        path.moveTo(startPoint->scenePos());
        path.lineTo(startPoint->scenePos());
        m_tempWire->setPath(path);
    }
}

void Canvas::completeWireCreation(ConnectionPoint* endPoint)
{
    if (m_creatingWire && m_wireStartPoint && endPoint && m_tempWire) {
        // Check if connection is valid (output to input)
        bool validConnection = false;
        
        if (m_wireStartPoint->getType() == ConnectionPoint::Output && 
            endPoint->getType() == ConnectionPoint::Input) {
            validConnection = true;
        } else if (m_wireStartPoint->getType() == ConnectionPoint::Input && 
                  endPoint->getType() == ConnectionPoint::Output) {
            // Swap start and end points
            ConnectionPoint* temp = m_wireStartPoint;
            m_wireStartPoint = endPoint;
            endPoint = temp;
            validConnection = true;
        }
        
        if (validConnection) {
            // Create a permanent wire
            Wire* wire = new Wire(m_wireStartPoint, endPoint);
            
            // Add wire to the scene and lists
            addItem(wire);
            m_wires.append(wire);
            
            // Connect the wire to the connection points
            m_wireStartPoint->addWire(wire);
            endPoint->addWire(wire);
            
            // Initial propagation of value from start point
            wire->propagateValue(m_wireStartPoint->getValue());
        }
        
        // Clean up temporary wire
        removeItem(m_tempWire);
        delete m_tempWire;
        m_tempWire = nullptr;
        
        m_creatingWire = false;
        m_wireStartPoint = nullptr;
    }
}

void Canvas::cancelWireCreation()
{
    if (m_creatingWire) {
        m_creatingWire = false;
        m_wireStartPoint = nullptr;
        
        if (m_tempWire) {
            removeItem(m_tempWire);
            delete m_tempWire;
            m_tempWire = nullptr;
        }
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Update temporary wire during creation
    if (m_creatingWire && m_tempWire) {
        QPointF endPos = event->scenePos();
        
        // Create a temporary path for the wire
        QPainterPath path;
        QPointF startPos = m_wireStartPoint->scenePos();
        
        path.moveTo(startPos);
        
        // Create a nice curved path
        qreal dx = endPos.x() - startPos.x();
        path.cubicTo(
            startPos.x() + dx * 0.5, startPos.y(),
            endPos.x() - dx * 0.5, endPos.y(),
            endPos.x(), endPos.y()
        );
        
        m_tempWire->setPath(path);
    }
    
    QGraphicsScene::mouseMoveEvent(event);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Check if we're creating a wire and released over a connection point
    if (m_creatingWire) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        ConnectionPoint* connectionPoint = dynamic_cast<ConnectionPoint*>(item);
        
        if (connectionPoint && connectionPoint != m_wireStartPoint) {
            completeWireCreation(connectionPoint);
        } else {
            // Released in empty space, cancel wire creation
            cancelWireCreation();
        }
    }
    
    QGraphicsScene::mouseReleaseEvent(event);
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    // Cancel wire creation with Escape key
    if (event->key() == Qt::Key_Escape && m_creatingWire) {
        cancelWireCreation();
        event->accept();
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}
