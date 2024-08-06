#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class Canvas;

enum ComponentType{DEFAULT = 0, INPUT , OUTPUT, AND,OR,EXOR, NAND, NOR, NOT};

class Component : public QGraphicsItem {
public:
    explicit Component(ComponentType type, QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override = 0;
    virtual QList<QPointF> getConnectionPoints() = 0;
    QVector2D getPosition();
    ComponentType getType() const;
    virtual void handleLogic() = 0;

    virtual ~Component();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;  
    ComponentType m_type;
};

#endif // COMPONENT_H
