#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class Canvas;

class Component : public QGraphicsItem {
public:
    explicit Component(QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override = 0;
    virtual QList<QPointF> getConnectionPoints() = 0;
    QVector2D getPosition();
    virtual void handleLogic() = 0;

    //Virtual functions for Connection points
    virtual void initConnectionPoints() = 0;
    virtual void updateConnectionPoints() = 0;
    virtual ~Component();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;  
};

#endif // COMPONENT_H
