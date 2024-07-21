#include "andgate.h"
#include <QPainter>
#include <QFile>
#include <QDebug>

AndGate::AndGate(QGraphicsItem *parent)
    : Component(parent)
{
    QString resourcePath = ":/new/prefix1/and_gate.png";
    m_pixmap = QPixmap(resourcePath);

    if (!QFile::exists(resourcePath)) {
        qDebug() << "Resource file does not exist:" << resourcePath;
    }

    if (m_pixmap.isNull()) {
        qDebug() << "Failed to load" << resourcePath;
    } else {
        qDebug() << "Successfully loaded" << resourcePath;
    }
}

QRectF AndGate::boundingRect() const {
    return QRectF(0, 0, m_pixmap.width(), m_pixmap.height());
}

void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, m_pixmap);
}
