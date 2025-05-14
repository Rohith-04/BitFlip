#include "inputcomponent.h"
#include "connectionpoint.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

InputComponent::InputComponent(QGraphicsItem *parent)
    : Component(parent),
      m_value(false)
{
    // Create label
    m_label = new QGraphicsTextItem("0", this);
    m_label->setPos(15, 10);
    
    // Initialize connection points
    initConnectionPoints();
}

InputComponent::~InputComponent()
{
}

QRectF InputComponent::boundingRect() const
{
    return QRectF(0, 0, SIZE, SIZE);
}

void InputComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    // Draw the input component
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QBrush(m_value ? Qt::green : Qt::red));
    
    // Draw the body
    painter->drawRect(0, 0, SIZE, SIZE);
    
    // Draw output line
    painter->drawLine(SIZE, SIZE/2, SIZE+10, SIZE/2);
}

QList<QPointF> InputComponent::getConnectionPoints()
{
    QList<QPointF> points;
    points << QPointF(SIZE+10, SIZE/2); // Output
    return points;
}

void InputComponent::handleLogic()
{
    // Nothing to do here, value is set by user
}

void InputComponent::initConnectionPoints()
{
    // Create output connection point
    auto* output = new ConnectionPoint(this, ConnectionPoint::Output, 0);
    output->setPos(SIZE+10, SIZE/2);
    m_connectionPoints.append(output);
    output->setValue(m_value);
}

void InputComponent::updateConnectionPoints()
{
    // Update connection point positions if the component moves
    if (!m_connectionPoints.isEmpty()) {
        m_connectionPoints[0]->setPos(SIZE+10, SIZE/2);
    }
}

bool InputComponent::getOutputValue(int index) const
{
    Q_UNUSED(index); // We only have one output
    return m_value;
}

void InputComponent::setInputValue(int index, bool value)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    // This is an input component, so it doesn't receive input from other components
}

void InputComponent::toggle()
{
    m_value = !m_value;
    
    // Update the label
    m_label->setPlainText(m_value ? "1" : "0");
    
    // Update the output connection point
    if (!m_connectionPoints.isEmpty()) {
        m_connectionPoints[0]->setValue(m_value);
    }
    
    // Trigger a redraw
    update();
}

void InputComponent::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        toggle();
        event->accept();
    } else {
        Component::mouseDoubleClickEvent(event);
    }
}