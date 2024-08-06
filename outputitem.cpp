#include "outputitem.h"
#include "connection.h"
#include <QPainter>
#include <QDebug>

int OutputItem::count = 0;

OutputItem::OutputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent)
    : Component(OUTPUT, parent), m_active(false), m_id(count++)
{
    m_activePixmap = QPixmap(activeImagePath);
    m_inactivePixmap = QPixmap(inactiveImagePath);

    // Check if pixmaps are loaded
    if (m_activePixmap.isNull() || m_inactivePixmap.isNull()) {
        qDebug() << "Failed to load output images:" << activeImagePath << inactiveImagePath;
    }

    m_outputData.position = QVector2D(pos().x(), pos().y());
    m_outputData.id = m_id;
}

QRectF OutputItem::boundingRect() const {
    return QRectF(0, 0, m_activePixmap.width(), m_activePixmap.height());
}

void OutputItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (m_active) {
        painter->drawPixmap(0, 0, m_activePixmap);
    }
    else {
        painter->drawPixmap(0, 0, m_inactivePixmap);
    }
}


void OutputItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_active = !m_active;
        update(); // Redraw the item
        qDebug() << getType();
    }
    Component::mousePressEvent(event);
}


void OutputItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    // Handle mouse release if needed
    Component::mouseReleaseEvent(event);
}

QList<QPointF> OutputItem::getConnectionPoints() {
    QRectF bounds = boundingRect();
    QList<QPointF> points;
    QPointF t_point(bounds.left() + 3.5, bounds.top() + bounds.height() * 0.5);
    points << t_point;
    m_outputData.connectionPoint = t_point;
    return points;
}

OutputItem::OutputItemData OutputItem::getOutputItemData() const {
    return m_outputData;
}

void OutputItem::handleLogic() {
    // Find the connection this OutputItem is connected to
    for (Connection *connection : Connection::listOfConnections) {
        if (connection->m_connectionData.endComponent == this) {
            m_active = connection->getState();
            update(); // Redraw the item
            break; //since the outputs have only one connection
        }
    }
}
