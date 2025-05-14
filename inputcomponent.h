#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"

class InputComponent : public Component {
    Q_OBJECT

public:
    explicit InputComponent(QGraphicsItem *parent = nullptr);
    ~InputComponent() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QList<QPointF> getConnectionPoints() override;
    
    void handleLogic() override;
    void initConnectionPoints() override;
    void updateConnectionPoints() override;
    
    bool getOutputValue(int index = 0) const override;
    void setInputValue(int index, bool value) override;
    
    // Toggle the output value
    void toggle();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int SIZE = 40;
    bool m_value;
    QGraphicsTextItem* m_label;
};

#endif // INPUTCOMPONENT_H