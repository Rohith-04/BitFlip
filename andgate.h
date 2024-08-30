#ifndef ANDGATE_H
#define ANDGATE_H

#include "component.h"
#include "gate.h"
#include <QPixmap>
#include <QVector2D>

class Canvas;

class AndGate : public Gate {
public:
    explicit AndGate(QGraphicsItem *parent = nullptr, NewProject *project = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    NewProject *m_project;
};

#endif // ANDGATE_H
