#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include "inputitem.h"
#include "outputitem.h"
#include "wire.h"
#include "connectionpoint.h"

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

public slots:
    void handleConnectionPointClick(ConnectionPoint* point);

private:

    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


    QList<InputItem *> inputItems;
    QList<OutputItem *> outputItems;
    QGraphicsView *view;

    Wire* currentWire;
    ConnectionPoint* startPoint;
    bool isDrawingWire;
};

#endif // CANVAS_H
