#ifndef INPUTITEM_H
#define INPUTITEM_H

#include "component.h"
#include <QString>
#include <QPixmap>
#include <QObject>

class NewProject; // Forward declaration

class InputItem : public Component {
    Q_OBJECT

public:
    InputItem(const QString& activeImagePath, const QString& inactiveImagePath, 
              QGraphicsItem *parent = nullptr, QObject *parentObj = nullptr);
    ~InputItem() override;

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
    QPixmap m_activeImage;
    QPixmap m_inactiveImage;
};

#endif // INPUTITEM_H
