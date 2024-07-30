#ifndef OUTPUTITEM_H
#define OUTPUTITEM_H

#include "component.h"

class OutputItem : public Component
{
public:
    OutputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void toggleState();
    QList<QPointF> getConnectionPoints() const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap m_activePixmap;
    QPixmap m_inactivePixmap;
    bool m_active;
};

#endif // OUTPUTITEM_H
