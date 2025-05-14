#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector2D>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QPointF>

class Canvas; // Forward declaration
class ConnectionPoint;

class Component : public QObject, public QGraphicsItem { // QObject first to avoid diamond inheritance
    Q_OBJECT // Required for signals and slots
    Q_INTERFACES(QGraphicsItem) // Required for QGraphicsItem with QObject

public:
    explicit Component(QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override = 0;
    virtual QList<QPointF> getConnectionPoints() = 0;
    QVector2D getPosition();
    virtual void handleLogic() = 0;

    //Virtual functions for Connection points
    virtual void initConnectionPoints() = 0;
    virtual void updateConnectionPoints() = 0;
    virtual ~Component() override;

    // Add methods to get input/output values
    virtual bool getOutputValue(int index = 0) const = 0;
    virtual void setInputValue(int index, bool value) = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
    Canvas *m_canvas;
    QList<ConnectionPoint*> m_connectionPoints;
};

#endif // COMPONENT_H
