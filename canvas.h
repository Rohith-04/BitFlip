#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QObject>
#include <QList>
#include "component.h"
class Canvas : public QGraphicsScene {
    Q_OBJECT

public:
    Canvas(QObject *parent = nullptr);

    void addComponent(QGraphicsItem *comp);
    void setView(QGraphicsView *view);
    void positionInputItems(const QList<QGraphicsItem *> &inputItems);
    void positionOutputItems(const QList<QGraphicsItem *> &outputItems);

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:
    QGraphicsView *view;
    bool isPanning;
    QPoint lastPos;
};

#endif // CANVAS_H
