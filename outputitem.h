#ifndef OUTPUTITEM_H
#define OUTPUTITEM_H

#include "component.h"
#include <QPixmap>
#include <QVector2D>
#include <QGraphicsSceneMouseEvent>

class OutputItem : public Component
{
public:
    struct OutputItemData {
        QVector2D position;
        int id;
        QPointF connectionPoint;
    };

    OutputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void toggleState();
    QList<QPointF> getConnectionPoints() override;
    OutputItemData getOutputItemData() const;

protected:
    // Uncomment and implement if mouse press events are needed
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPixmap m_activePixmap;
    QPixmap m_inactivePixmap;
    bool m_active;
    int m_id; // Unique identifier for each output item
    static int count; // Static counter to generate unique IDs

    OutputItemData m_outputData; // Store instance-specific data
};

#endif // OUTPUTITEM_H
