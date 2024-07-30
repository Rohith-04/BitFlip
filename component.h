#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class Component : public QGraphicsItem {
public:
    explicit Component(QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override = 0;
    virtual QList<QPointF> getConnectionPoints() const = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;    
};

#endif // COMPONENT_H
