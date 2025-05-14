#ifndef OUTPUTCOMPONENT_H
#define OUTPUTCOMPONENT_H

#include "component.h"
#include <QObject>

class OutputComponent : public Component {
    Q_OBJECT

public:
    explicit OutputComponent(QGraphicsItem *parent = nullptr, QObject *parentObj = nullptr);
    ~OutputComponent() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QList<QPointF> getConnectionPoints() override;
    
    void handleLogic() override;
    void initConnectionPoints() override;
    void updateConnectionPoints() override;
    
    bool getOutputValue(int index = 0) const override;
    void setInputValue(int index, bool value) override;

private:
    static const int SIZE = 40;
    bool m_value;
    QGraphicsTextItem* m_label;
};

#endif // OUTPUTCOMPONENT_H