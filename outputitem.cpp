#include "outputitem.h"
#include "connectionpoint.h"
#include <QPainter>

// Make sure the class name is consistent throughout the file
OutputItem::OutputItem(QGraphicsItem *parent, QObject *parentObj)
    : Component(parent),
      m_value(false),
      m_active(false),
    m_radius(5.0)
{
    // Set parent object if provided
    if (parentObj) {
        setParent(parentObj);
    }
    
    // Load pixmaps
    m_activePixmap.load(":/images/assets/op-active.png");
    m_inactivePixmap.load(":/images/assets/op-not_active.png");
    
    // Create label
    m_label = new QGraphicsTextItem("0", this);
    m_label->setPos(15, 10);
    
    // Initialize connection points
    initConnectionPoints();
}

OutputItem::~OutputItem()
{
    // Cleanup if needed
}

void OutputItem::initConnectionPoints()
{
    // Create input connection point
    inputTerminal = new ConnectionPoint(this, ConnectionPoint::Input, 0);
    
    // Update positions
    updateConnectionPoints();
}

void OutputItem::updateConnectionPoints()
{
    QList<QPointF> connectionPoints = getConnectionPoints();

    // Use a fixed radius value instead of calling getRadius()
    float r = 5.0; // Standard connection point radius
    inputTerminal->setPos(connectionPoints[0].x() - r, connectionPoints[0].y() - r);
}


QRectF OutputItem::boundingRect() const 
{
    return QRectF(0, 0, m_activePixmap.width(), m_activePixmap.height());
}

void OutputItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) 
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (m_active) {
        painter->drawPixmap(0, 0, m_activePixmap);
    }
    else {
        painter->drawPixmap(0, 0, m_inactivePixmap);
    }
}

QList<QPointF> OutputItem::getConnectionPoints() 
{
    QRectF bounds = boundingRect();
    QList<QPointF> points;
    QPointF t_point(bounds.left() + 3.5, bounds.top() + bounds.height() * 0.5);
    points << t_point;
    return points;
}

void OutputItem::handleLogic() 
{
    // Update the output display based on input value
    // This is now handled by setInputValue
}

bool OutputItem::getOutputValue(int index) const
{
    Q_UNUSED(index);
    return m_value; // This is not used as this is an output component
}

void OutputItem::setInputValue(int index, bool value)
{
    if (index == 0 && m_value != value) {
        m_value = value;
        m_active = value;
        
        // Update the label
        m_label->setPlainText(m_value ? "1" : "0");
        
        // Trigger a redraw
        update();
    }
}
