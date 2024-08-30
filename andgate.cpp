#include "andgate.h"
#include "wire.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>
#include <utility>

AndGate::AndGate(QGraphicsItem *parent, NewProject *project) : Gate(parent, project) {

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
    qDebug() << "AndGate: " << m_project;
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, m_pixmap);
}


