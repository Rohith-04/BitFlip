#ifndef ANDGATE_H
#define ANDGATE_H

#include "component.h"
#include "gate.h"
#include <QPixmap>
#include <QVector2D>

class Canvas;

class AndGate : public Gate {
public:
    explicit AndGate(QGraphicsItem *parent = nullptr);

    struct AndGateData{
        QVector2D position;
        int id;
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    AndGateData m_andGateData; //Instance of the struct
};

#endif // ANDGATE_H
