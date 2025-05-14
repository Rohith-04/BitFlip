#include "outputcomponent.h"
#include "connectionpoint.h"
#include <QPainter>

OutputComponent::OutputComponent(QGraphicsItem *parent)
    : Component(parent),
      m_value(false)
{
    // Create label
    m_label = new QGraphicsTextItem("0", this);
    m_label->setPos(15, 10);
    
    // Initialize connection points
    initConnectionPoints();
}

OutputComponent::~OutputComponent()
{
}

QRectF OutputComponent::boundingRect() const
{
    return QRectF(0, 0, SIZE, SIZE);
}

void OutputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    // Draw the output component
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QBrush(m_value ? Qt::green : Qt::red));
    
    // Draw the body
    painter->drawRect(0, 0, SIZE, SIZE);
    
    // Draw input line
    painter->drawLine(-10, SIZE/2, 0, SIZE/2);
}

QList<QPointF> OutputComponent::getConnectionPoints()
{
    QList<QPointF> points;
    points << QPointF(-10, SIZE/2); // Input
    return points;
}

void OutputComponent::handleLogic()
{
    // Nothing to do here, value is set by connected components
}

void OutputComponent::initConnectionPoints()
{
    // Create input connection point
    auto* input = new ConnectionPoint(this, ConnectionPoint::Input, 0);
    input->setPos(-10, SIZE/2);
    m_connectionPoints.append(input);
}

void OutputComponent::updateConnectionPoints()
{
    // Update connection point positions if the component moves
    if (!m_connectionPoints.isEmpty()) {
        m_connectionPoints[0]->setPos(-10, SIZE/2);
    }
}

bool OutputComponent::getOutputValue(int index) const
{
    Q_UNUSED(index);
    return m_value; // This is not used as this is an output component
}

void OutputComponent::setInputValue(int index, bool value)
{
    if (index == 0 && m_value != value) {
        m_value = value;
        
        // Update the label
        m_label->setPlainText(m_value ? "1" : "0");
        
        // Trigger a redraw
        update();
    }
}