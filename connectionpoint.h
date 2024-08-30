#ifndef CONNECTIONPOINT_H
#define CONNECTIONPOINT_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include "wire.h"
//#include "canvas.h"

class NewProject; //Forward declaration of the new project class

class ConnectionPoint :  public QObject , public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit ConnectionPoint(QGraphicsItem *parent = nullptr, NewProject *project = nullptr);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    float getRadius();

signals:
    void ConnectionPointClicked();

private:
    float radius;
    QPen pen;
    QColor defaultColor;
    QColor hoverColor;

/////////////////////////////////////
    NewProject *m_project;

};

#endif // CONNECTIONPOINT_H
