// wire.h
#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsPathItem>
#include <QObject>

class ConnectionPoint;

class Wire : public QObject, public QGraphicsPathItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Wire(ConnectionPoint* startPoint = nullptr, ConnectionPoint* endPoint = nullptr, QGraphicsItem* parent = nullptr);
    ~Wire() override;

    void setStartPoint(ConnectionPoint* point);
    void setEndPoint(ConnectionPoint* point);
    
    ConnectionPoint* getStartPoint() const { return m_startPoint; }
    ConnectionPoint* getEndPoint() const { return m_endPoint; }
    
    void updatePath();
    void disconnect();
    void propagateValue(bool value);

private slots:
    void onStartPointValueChanged(bool value);

private:
    ConnectionPoint* m_startPoint;
    ConnectionPoint* m_endPoint;
    bool m_value;
    
    void updateAppearance();
};

#endif // WIRE_H