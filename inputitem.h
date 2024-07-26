#ifndef INPUTITEM_H
#define INPUTITEM_H

#include "component.h"
#include <QPixmap>
#include "canvas.h"
class InputItem : public Component {
public:
    InputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void toggleState();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap m_activePixmap;
    QPixmap m_inactivePixmap;
    bool m_active;
};

#endif // INPUTITEM_H
