#ifndef ANDGATE_H
#define ANDGATE_H

#include "component.h"
#include <QPixmap>

class AndGate : public Component {
public:
    explicit AndGate(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPixmap m_pixmap;
};

#endif // ANDGATE_H
