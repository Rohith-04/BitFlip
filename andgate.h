#ifndef ANDGATE_H
#define ANDGATE_H

#include "component.h"
#include <QGraphicsTextItem>
#include <QObject>

class NewProject; // Forward declaration

class AndGate : public Component {
    Q_OBJECT

public:
    explicit AndGate(QGraphicsItem *parent = nullptr, QObject *parentObj = nullptr);
    ~AndGate() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QList<QPointF> getConnectionPoints() override;
    
    void handleLogic() override;
    void initConnectionPoints() override;
    void updateConnectionPoints() override;
    
    bool getOutputValue(int index = 0) const override;
    void setInputValue(int index, bool value) override;

private:
    static const int WIDTH = 60;
    static const int HEIGHT = 60;
    
    bool m_input1;
    bool m_input2;
    bool m_output;
    QGraphicsTextItem* m_label;
};

#endif // ANDGATE_H
