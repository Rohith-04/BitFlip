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
    };

    //std::vector<AndGateData> listOfAndComponents;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; //have to override this function to update connectionPoints
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    bool getState();
    QList<QPointF> getConnectionPoints () override;

    void handleLogic() override;
private:
    QPixmap m_pixmap;
    int m_id;
    static int count;
    bool state;
    //variables which hold state for the input terminals
    bool input1;
    bool input2;

    AndGateData m_andGateData;
};

#endif // ANDGATE_H
