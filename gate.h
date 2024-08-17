#ifndef GATE_H
#define GATE_H

#include "component.h"
#include "canvas.h"

class Gate : public Component {
public:
    explicit Gate(QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    QList<QPointF> getConnectionPoints() override;
    void handleLogic() override{}

    //Mouse Handling Functions
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; //have to override this function to update connectionPoints
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    //Setters
    void setFirstInput(bool val);
    void setSecondInput(bool val);
    void setOutput(bool val);
    //Getters
    bool getFirstInput(void);
    bool getSecondInput(void);
    bool getOutput(void);

//Attributes

    QPixmap m_pixmap;
    bool output;
    bool firstInput;
    bool secondInput;
};

#endif // GATE_H
