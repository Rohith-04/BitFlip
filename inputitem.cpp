#include "inputitem.h"
#include "connection.h"
#include <QPainter>
#include <QDebug>

int InputItem::count = 0;

InputItem::InputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent)
    : Component(parent), m_active(false), m_id(count++)
{
    m_activePixmap = QPixmap(activeImagePath);
    m_inactivePixmap = QPixmap(inactiveImagePath);
    state = false;

    // Check if pixmaps are loaded
    if (m_activePixmap.isNull() || m_inactivePixmap.isNull()) {
        qDebug() << "Failed to load input images:" << activeImagePath << inactiveImagePath;
    }

    m_inputData.position = QVector2D(pos().x(), pos().y());
    m_inputData.id = m_id;
}

QRectF InputItem::boundingRect() const {
    return QRectF(0, 0, m_activePixmap.width(), m_activePixmap.height());
}

void InputItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_active) {
        painter->drawPixmap(0, 0, m_activePixmap);
    } else {
        painter->drawPixmap(0, 0, m_inactivePixmap);
    }
}

void InputItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_active = !m_active;
        update(); // Redraws the item
        state = !state;

        //Update the wire it is connected to
        for (Connection *connection : Connection::listOfConnections) {
            if (connection->m_connectionData.startComponent == this) {
                connection->setState(m_active);
                connection->m_connectionData.state = m_active; //update it also in its corresponding struct so that it can be accessed later in the logic evaluation
            }
        }
    }
    Component::mousePressEvent(event);
}

void InputItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        // Handle movement
        Component::mouseMoveEvent(event);

        // Update the position of the connection points
        m_inputData.position = QVector2D(pos().x(), pos().y());

        qDebug() << "Item moved to position:" << m_inputData.position;
    }
}

void InputItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    // Handle mouse release if needed
    Component::mouseReleaseEvent(event);
}

QList<QPointF> InputItem::getConnectionPoints() {
    QList<QPointF> points;
    QRectF bounds = boundingRect();

    QPointF t_point(bounds.right() - 1.5, bounds.top() + bounds.height() * 0.5);
    points << t_point;

    for (const auto &point : points) {
        qDebug() << "Connection point:" << point;
    }

    return points;
}

bool InputItem::getState(){
    return state;
}
