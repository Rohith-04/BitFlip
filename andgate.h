#ifndef ANDGATE_H
#define ANDGATE_H

#include "component.h"
#include <QPixmap>
#include <QVector2D>

class Canvas;

enum TerminalType{
    Input,
    Output
};

struct ConnectionPoint{
    TerminalType terminalType;
    bool isActive;
};

class AndGate : public Component {
public:
    explicit AndGate(QGraphicsItem *parent = nullptr);

    struct AndGateData{
        QVector2D position;
        int id;
        std::vector<ConnectionPoint> connectionPoints; // A struct which holds the type of connnectionPoint and their states
    };

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; //have to override this function to update connectionPoints
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QList<QPointF> getConnectionPoints () override;

    void handleLogic() override;
private:
    QPixmap m_pixmap;
    int m_id;
    static int count;

    AndGateData m_andGateData;
};

#endif // ANDGATE_H
