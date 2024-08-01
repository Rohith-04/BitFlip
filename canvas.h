#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include "inputitem.h"
#include "outputitem.h"
#include "connection.h"

class Component;
class InputItem;
class OutputItem;

class Canvas : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = nullptr);

    void addComponent(QGraphicsItem *comp);
    void addComponent(QGraphicsLineItem *line);
    void setView(QGraphicsView *view);
    void repositionItems();

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:


    QGraphicsView *view;
    QList<InputItem *> inputItems;
    QList<OutputItem *> outputItems;

    Connection* currentConnection;
    bool isDrawingConnection;
    QPointF lastPoint;

    std::pair<QPointF, Component *> getNearestConnectionPoint(const QPointF &scenePos);
    Component *startComponent;

    Qt::Orientation lastDirection;

};

#endif // CANVAS_H
