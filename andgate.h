#ifndef ANDGATE_H
#define ANDGATE_H

#include "component.h"
#include <QPixmap>
#include <QVector2D>

class Canvas;

class AndGate : public Component {
public:
    explicit AndGate(QGraphicsItem *parent = nullptr);

    struct AndGateData{
        QVector2D position;
        int id;
        QList<QPointF> connectionPoints;
    };

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QList<QPointF> getConnectionPoints () override;

    void handleLogic() {}
private:
    QPixmap m_pixmap;
    int m_id;
    static int count;

    AndGateData m_andGateData;
};

#endif // ANDGATE_H
