#ifndef INPUTITEM_H
#define INPUTITEM_H

#include "component.h"
#include <QPixmap>
#include <QVector2D>
#include <QGraphicsSceneMouseEvent>

class InputItem : public Component {
public:
    struct InputItemData {
        QVector2D position;
        int id;
        QPointF connectionPoint;
    };   
    InputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool getState();
    QList<QPointF> getConnectionPoints() override;
    InputItemData getInputItemData() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap m_activePixmap;
    QPixmap m_inactivePixmap;
    bool m_active;
    bool state;
    int m_id; // Unique identifier for each input item
    static int count; // Static counter to generate unique IDs

    InputItemData m_inputData; // Store instance-specific data
};

#endif // INPUTITEM_H
