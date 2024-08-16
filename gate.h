#ifndef GATE_H
#define GATE_H

#include "component.h"

class Gate : public Component {
public:
    explicit Gate(QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; //have to override this function to update connectionPoints
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QList<QPointF> getConnectionPoints() override;
    void handleLogic() override{}

    //Mouse Handling Functions
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    //Setters
    void setInput1(bool val);
    void setInput2(bool val);
    void setState(bool val);
    //Getters
    bool getInput(void);
    bool getInput2(void);
    bool getState(void);

//Attributes

    QPixmap m_pixmap;
    bool state;
    bool input1;
    bool input2;
};

#endif // GATE_H
