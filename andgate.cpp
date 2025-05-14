#include "andgate.h"
#include "connectionpoint.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

AndGate::AndGate(QGraphicsItem *parent, QObject *parentObj)
    : Component(parent),
      m_input1(false),
      m_input2(false),
      m_output(false)
{
    // Set parent object if provided
    if (parentObj) {
        setParent(parentObj);
    }
    
    // Create label
    m_label = new QGraphicsTextItem("AND", this);
    m_label->setPos(15, 20);
    
    // Initialize connection points
    initConnectionPoints();
}

AndGate::~AndGate()
{
}

QRectF AndGate::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    // Draw the AND gate shape
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(QBrush(Qt::white));
    
    // Draw the body
    QRectF rect(10, 10, 40, 40);
    painter->drawRect(rect);
    
    // Draw input and output lines
    painter->drawLine(0, 20, 10, 20);  // Input 1
    painter->drawLine(0, 40, 10, 40);  // Input 2
    painter->drawLine(50, 30, 60, 30); // Output
}

QList<QPointF> AndGate::getConnectionPoints()
{
    QList<QPointF> points;
    points << QPointF(0, 20);  // Input 1
    points << QPointF(0, 40);  // Input 2
    points << QPointF(60, 30); // Output
    return points;
}

void AndGate::handleLogic()
{
    // Perform AND logic
    bool newOutput = m_input1 && m_input2;
    
    // Update output if changed
    if (m_output != newOutput) {
        m_output = newOutput;
        
        // Update the output connection point
        for (auto* point : m_connectionPoints) {
            if (point->getType() == ConnectionPoint::Output) {
                point->setValue(m_output);
            }
        }
    }
}

void AndGate::initConnectionPoints()
{
    // Create input connection points
    auto* input1 = new ConnectionPoint(this, ConnectionPoint::Input, 0);
    input1->setPos(0, 20);
    m_connectionPoints.append(input1);
    
    auto* input2 = new ConnectionPoint(this, ConnectionPoint::Input, 1);
    input2->setPos(0, 40);
    m_connectionPoints.append(input2);
    
    // Create output connection point
    auto* output = new ConnectionPoint(this, ConnectionPoint::Output, 0);
    output->setPos(60, 30);
    m_connectionPoints.append(output);
}

void AndGate::updateConnectionPoints()
{
    // Update connection point positions if the component moves
    if (m_connectionPoints.size() >= 3) {
        m_connectionPoints[0]->setPos(0, 20);  // Input 1
        m_connectionPoints[1]->setPos(0, 40);  // Input 2
        m_connectionPoints[2]->setPos(60, 30); // Output
    }
}

bool AndGate::getOutputValue(int index) const
{
    Q_UNUSED(index); // We only have one output
    return m_output;
}

void AndGate::setInputValue(int index, bool value)
{
    if (index == 0) {
        m_input1 = value;
    } else if (index == 1) {
        m_input2 = value;
    }
    
    // Update logic after input change
    handleLogic();
}
