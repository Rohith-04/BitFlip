// connection.h
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>
#include <QPainterPath>

class Connection : public QGraphicsPathItem {
public:
    Connection(QGraphicsItem *parent = nullptr);

    void addPoint(const QPointF &point);
    void setColor(const QColor &color);
    void setActive(bool active);
    QRectF boundingRect() const ;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPainterPath path;
    QColor color;
    bool isActive;
};

#endif // CONNECTION_H
