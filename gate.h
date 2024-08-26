#ifndef GATE_H
#define GATE_H

#include "component.h"
#include "canvas.h"
#include "connectionpoint.h"
#include <QObject>

class Gate : public Component {
public:
    explicit Gate(QGraphicsItem *parent = nullptr);
    void initConnectionPoints() override; //Initialises Connection Points and will be calling this when the button is pressed in the newproject class

protected:
    QRectF boundingRect() const override;
    QList<QPointF> getConnectionPoints() override;
    void updateConnectionPoints() override; //Updates the connection points when the gate is moving
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

//ConnectionPoints Attributs
    ConnectionPoint *input1;
    ConnectionPoint *input2;
    ConnectionPoint *outputPoint; //there is already a output member so a workaround

//Wire related things
    Canvas *m_canvas;
};

#endif // GATE_H
