#include "outputitem.h"
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QGraphicsSceneMouseEvent>

OutputItem::OutputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent)
            :Component(parent), m_active(false)
{
    m_activePixmap = QPixmap(activeImagePath);
    m_inactivePixmap = QPixmap(inactiveImagePath);
    // Check if pixmaps are loaded
    if (m_activePixmap.isNull() || m_inactivePixmap.isNull()) {
        qDebug() << "Failed to load output images:" << activeImagePath << inactiveImagePath;
    }
}

QRectF OutputItem::boundingRect() const{
    return QRect(0,0,m_activePixmap.width(), m_activePixmap.height());
}

void OutputItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (m_active) {
        painter->drawPixmap(0, 0, m_activePixmap);
    } else {
        painter->drawPixmap(0, 0, m_inactivePixmap);
    }
}

void OutputItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_active = !m_active;
        update(); // Redraw the item
    }
    Component::mousePressEvent(event);
}

void OutputItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    // Handle mouse release if needed
    Component::mouseReleaseEvent(event);
}
