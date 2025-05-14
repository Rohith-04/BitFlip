#ifndef OUTPUTITEM_H
#define OUTPUTITEM_H

#include "component.h"
#include <QGraphicsTextItem>
#include <QPixmap>

class OutputItem : public Component {
    Q_OBJECT

public:
    explicit OutputItem(QGraphicsItem *parent = nullptr, QObject *parentObj = nullptr);
    ~OutputItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QList<QPointF> getConnectionPoints() override;
    
    void handleLogic() override;
    void initConnectionPoints() override;
    void updateConnectionPoints() override;
    
    bool getOutputValue(int index = 0) const;
    void setInputValue(int index, bool value);
    float getRadius() const { return m_radius; }

private:
    bool m_value;
    bool m_active;
    QPixmap m_activePixmap;
    QPixmap m_inactivePixmap;
    QGraphicsTextItem* m_label;
    ConnectionPoint* inputTerminal;
    float m_radius;
};

#endif // OUTPUTITEM_H
