#include "andgate.h"
#include "wire.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>
#include <utility>

AndGate::AndGate(QGraphicsItem *parent) : Gate(parent) {

    QString resourcePath = ":/images/assets/and_gate.svg";
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
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, m_pixmap);
}

/*
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
*/
