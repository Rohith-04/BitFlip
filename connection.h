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
        bool state;
    };
    static std::vector<Connection *> listOfConnections;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void addPoint(const QPointF &point);
    void setColor(const QColor &color);
    void setActive(bool active);
    void setState(bool state);
    QRectF boundingRect() const override;

    bool getState();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    ConnectionData m_connectionData; //Instance of the struct
    //void logicHandling();

private:
    QPainterPath path;
    QColor color;
    bool isActive;
    int m_id;
    static int count;
};

#endif // CONNECTION_H
