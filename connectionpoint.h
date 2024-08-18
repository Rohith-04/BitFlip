#ifndef CONNECTIONPOINT_H
#define CONNECTIONPOINT_H

#include <QGraphicsEllipseItem>
#include <QPen>

class ConnectionPoint : public QGraphicsEllipseItem
{
public:
    explicit ConnectionPoint(QGraphicsItem *parent = nullptr);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    float getRadius();
    ~ConnectionPoint();

private:
    float radius;
    QPen pen;
    QColor defaultColor;
    QColor hoverColor;
};

#endif // CONNECTIONPOINT_H
