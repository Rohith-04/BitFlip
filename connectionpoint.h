#ifndef CONNECTIONPOINT_H
#define CONNECTIONPOINT_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include "wire.h"
//#include "canvas.h"

class ConnectionPoint : public QGraphicsEllipseItem
{
public:
    explicit ConnectionPoint(QGraphicsItem *parent = nullptr);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    Wire* getCurrentWire();
    void setCurrentWire(Wire *wire);

    float getRadius();
    ~ConnectionPoint();

signals:
    void connectionPointClicked(ConnectionPoint* point);

private:
    float radius;
    QPen pen;
    QColor defaultColor;
    QColor hoverColor;


};

#endif // CONNECTIONPOINT_H
