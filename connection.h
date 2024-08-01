// connection.h
#ifndef CONNECTION_H
#define CONNECTION_H

#include "component.h"
#include <QGraphicsPathItem>
#include <QPainterPath>

class Connection : public QGraphicsPathItem {
public:
    Connection(QGraphicsItem *parent = nullptr);
    
    struct ConnectionData{
        int id;
        Component *startComponent;
        Component *endComponent;
        QPointF startPosition;
        QPointF endPosition;
    };

    void addPoint(const QPointF &point);
    void setColor(const QColor &color);
    void setActive(bool active);
    QRectF boundingRect() const ;

    void setState(bool state);
    bool getState();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPainterPath path;
    QColor color;
    bool isActive;
    int m_id;
    static int count;
    ConnectionData m_connectionData;
};

#endif // CONNECTION_H
