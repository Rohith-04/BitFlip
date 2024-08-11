#include "andgate.h"
#include "connection.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>
#include <utility>

int AndGate::count = 0;

AndGate::AndGate(QGraphicsItem *parent)
    : Component(AND, parent)
{
    state = false;
    input1 = false;
    input2 = false;

    QString resourcePath = ":/images/assets/and_gate.png";
    m_pixmap = QPixmap(resourcePath);

    if (!QFile::exists(resourcePath)) {
        qDebug() << "Resource file does not exist:" << resourcePath;
    }

    if (m_pixmap.isNull()) {
        qDebug() << "Failed to load" << resourcePath;
    }
    else {
        qDebug() << "Successfully loaded" << resourcePath;
    }
    m_andGateData.position = QVector2D(pos().x(), pos().y());
    m_andGateData.id = m_id;

    count++;

    //listOfAndComponents.append(this);
}

QRectF AndGate::boundingRect() const {
    return QRectF(0, 0, m_pixmap.width(), m_pixmap.height());
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, m_pixmap);
}

void AndGate::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton){
        //Handles Movement
        Component::mouseMoveEvent(event);
        m_andGateData.position = QVector2D(pos().x(), pos().y());
        //qDebug() << m_andGateData.id;
        //qDebug() << "Item moved to position:" << m_andGateData.position;
        //qDebug() << getType();
    }
}

void AndGate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
    qDebug() << "Removing And Gate";
    if(scene()){
            scene()->removeItem(this);
    }
    delete this;
    }
}


QList<QPointF> AndGate::getConnectionPoints() {
    QList<QPointF> points;
    QRectF bounds = boundingRect();

    points << QPointF(static_cast<float>(bounds.left()), static_cast<float>(bounds.top()) + static_cast<float>(bounds.height()) * 0.25f);
    points << QPointF(static_cast<float>(bounds.left()), static_cast<float>(bounds.top()) + static_cast<float>(bounds.height()) * 0.75f);
    points << QPointF(static_cast<float>(bounds.right()), static_cast<float>(bounds.top()) + static_cast<float>(bounds.height()) * 0.5f);

    return points;
}

bool AndGate::getState(){
    return state;
}

void AndGate::handleLogic() {
    Connection *connection = nullptr;

    // Initialize inputs
    this->input1 = false;
    this->input2 = false;

    // Find the connection for input1
    for (auto &connection1 : Connection::listOfConnections) {
        if (connection1->m_connectionData.endComponent == this) {
            this->input1 = connection1->getState();
            connection = connection1;
            qDebug() << "input1 set to:" << this->input1;
            break;
        }
    }

    // Find the connection for input2, making sure it's not the same as the one for input1
    for (auto &connection2 : Connection::listOfConnections) {
        if (connection2->m_connectionData.endComponent == this && connection2 != connection) {
            this->input2 = connection2->getState();
            qDebug() << "input2 set to:" << this->input2;
            break;
        }
    }

    // Compute the state
    this->state = input1 && input2;
    qDebug() << "Computed state:" << this->state;

    // Update connections starting with this gate
    for (auto &connection3 : Connection::listOfConnections) {
        if (connection3->m_connectionData.startComponent == this) {
            connection3->setState(this->state);
            qDebug() << "Updated connection3 state to:" << this->state;
        }
    }
}

