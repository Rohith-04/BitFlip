#ifndef OUTPUTITEM_H
#define OUTPUTITEM_H

#include "connectionpoint.h"
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
    };

    OutputItem(const QString &activeImagePath, const QString &inactiveImagePath, QGraphicsItem *parent = nullptr, NewProject *project = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void toggleState();
    QList<QPointF> getConnectionPoints() override;

    void handleLogic() override;

    void initConnectionPoints() override;
    void updateConnectionPoints() override;

private:
    QPixmap m_activePixmap;
    QPixmap m_inactivePixmap;
    bool m_active;
    int m_id; // Unique identifier for each output item
    static int count; // Static counter to generate unique IDs
    NewProject *m_project;

    OutputItemData m_outputData; // Instance of the struct

    ConnectionPoint *outputTerminal;
};

#endif // OUTPUTITEM_H
