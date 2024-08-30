// wire.h
#ifndef WIRE_H
#define WIRE_H

//#include "connectionpoint.h"
#include "component.h"
#include <QGraphicsPathItem>
#include <QPainterPath>

class ConnectionPoint;

class Wire : public QGraphicsPathItem {
public:
    Wire(QGraphicsItem *parent = nullptr);
    
    struct WireData{
        int id;
        Component *startComponent;
        Component *endComponent;
        QPointF startPosition;
        QPointF endPosition;
        bool state;
    };
    static std::vector<Wire *> listOfWires;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void addPoint(const QPointF &point);
    void setColor(const QColor &color);
    void setActive(bool active);
    void setState(bool state);
    QRectF boundingRect() const override;
    bool getState();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void updatePath(QPointF newPoint);
    WireData m_wireData; //Instance of the struct

private:
    QPainterPath path;
    QColor color;
    bool isActive;
    int m_id;
    static int count;
    //////////////////////WIRE////////////////////////////////////////////
};

#endif // WIRE_H
