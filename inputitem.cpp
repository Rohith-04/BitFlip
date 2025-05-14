#include "inputitem.h"
#include "connectionpoint.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

InputItem::InputItem(const QString& activeImagePath, const QString& inactiveImagePath, 
                     QGraphicsItem *parent, QObject *parentObj)
    : Component(parent),
      m_value(false)
{
    // Set parent object if provided
    if (parentObj) {
        setParent(parentObj);
    }
    
    // Load images
    m_activeImage.load(activeImagePath);
    m_inactiveImage.load(inactiveImagePath);
    
    // Initialize connection points
    initConnectionPoints();
}

InputItem::~InputItem()
{
}

QRectF InputItem::boundingRect() const
{
    return QRectF(0, 0, SIZE, SIZE);
}

void InputItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    // Draw the input component using the appropriate image
    if (m_value) {
        painter->drawPixmap(0, 0, SIZE, SIZE, m_activeImage);
    } else {
        painter->drawPixmap(0, 0, SIZE, SIZE, m_inactiveImage);
    }
    
    // Draw output line
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(SIZE, SIZE/2, SIZE+10, SIZE/2);
}

QList<QPointF> InputItem::getConnectionPoints()
{
    QList<QPointF> points;
    points << QPointF(SIZE+10, SIZE/2); // Output
    return points;
}

void InputItem::handleLogic()
{
    // Nothing to do here, value is set by user
}

void InputItem::initConnectionPoints()
{
    // Create output connection point
    auto* output = new ConnectionPoint(this, ConnectionPoint::Output, 0);
    output->setPos(SIZE+10, SIZE/2);
    m_connectionPoints.append(output);
    output->setValue(m_value);
}

void InputItem::updateConnectionPoints()
{
    // Update connection point positions if the component moves
    if (!m_connectionPoints.isEmpty()) {
        m_connectionPoints[0]->setPos(SIZE+10, SIZE/2);
    }
}

bool InputItem::getOutputValue(int index) const
{
    Q_UNUSED(index); // We only have one output
    return m_value;
}

void InputItem::setInputValue(int index, bool value)
{
    Q_UNUSED(index);
    Q_UNUSED(value);
    // This is an input component, so it doesn't receive input from other components
}

void InputItem::toggle()
{
    m_value = !m_value;
    
    // Update the output connection point
    if (!m_connectionPoints.isEmpty()) {
        m_connectionPoints[0]->setValue(m_value);
    }
    
    // Trigger a redraw
    update();
}

void InputItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        toggle();
        event->accept();
    } else {
        Component::mouseDoubleClickEvent(event);
    }
}
