#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QObject>
#include <QList>
#include <QGraphicsItem>

class Canvas : public QGraphicsScene {
    Q_OBJECT
public:
    Canvas(QObject *parent = nullptr);

    void addComponent(QGraphicsItem *comp);
    void setView(QGraphicsView *view);
    void updateItemPositions();
    void repositionItems();

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsView *view;
    QList<QGraphicsItem*> inputItems;
    QList<QGraphicsItem*> outputItems;
};

#endif // CANVAS_H
