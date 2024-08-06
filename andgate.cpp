#include "andgate.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>

int AndGate::count = 0;

AndGate::AndGate(QGraphicsItem *parent)
    : Component(AND, parent)
{
    QString resourcePath = ":/images/assets/and_gate.svg";
    m_pixmap = QPixmap(resourcePath);

    if (!QFile::exists(resourcePath)) {
        qDebug() << "Resource file does not exist:" << resourcePath;
    }

    if (m_pixmap.isNull()) {
        qDebug() << "Failed to load" << resourcePath;
    } else {
        qDebug() << "Successfully loaded" << resourcePath;
    }
    m_andGateData.position = QVector2D(pos().x(), pos().y());
    //m_andGateData.connectionPoints = getConnectionPoints();
    m_andGateData.id = m_id;

    count++;
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
        qDebug() << "AndGate moving";
        m_andGateData.position = QVector2D(pos().x(), pos().y());
        //m_andGateData.connectionPoints = getConnectionPoints();
        qDebug() << m_andGateData.id;
        //qDebug() << "Item moved to position:" << m_andGateData.position;
        //qDebug() << "Connection point updated to:" << m_andGateData.connectionPoints;
        qDebug() << getType();
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

    for(auto i = points.begin(); i != points.end(); ++i){
        qDebug() << "andGate------> " << (*i);
    }

    return points;
}

void AndGate::handleLogic(){

}
