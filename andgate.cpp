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
    Connection *inputConnection1 = nullptr;
    Connection *inputConnection2 = nullptr;
    Connection *outputConnection = nullptr;

    // Find the first and second input connections
    for (auto connection : Connection::listOfConnections) {
        if (connection->m_connectionData.endComponent == this) {
            if (!inputConnection1) {
                inputConnection1 = connection;
                this->input1 = connection->getState();
            } else if (connection != inputConnection1) {
                inputConnection2 = connection;
                this->input2 = connection->getState();
            }
        }
    }

    //And Gate Logic
    this->state = this->input1 && this->input2;

    // Find the output connection and set its state
    for (auto connection : Connection::listOfConnections) {
        if (connection->m_connectionData.startComponent == this) {
            outputConnection = connection;
            outputConnection->setState(this->state);
            break;  // Assuming only one output connection
        }
    }
}

