#ifndef CONNECTIONPOINT_H
#define CONNECTIONPOINT_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Component;
class Wire;
class NewProject; // Forward declaration

class ConnectionPoint : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum Type { Input, Output };

    ConnectionPoint(Component* parent, Type type, int index = 0);
    ~ConnectionPoint() override;

    Type getType() const { return m_type; }
    int getIndex() const { return m_index; }
    Component* getParentComponent() const { return m_parentComponent; }
    
    void addWire(Wire* wire);
    void removeWire(Wire* wire);
    QList<Wire*> getConnectedWires() const { return m_connectedWires; }
    
    bool getValue() const { return m_value; }
    void setValue(bool value);

signals:
    void valueChanged(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    
private:
    Component* m_parentComponent;
    Type m_type;
    int m_index;
    bool m_value;
    QList<Wire*> m_connectedWires;
};

#endif // CONNECTIONPOINT_H
