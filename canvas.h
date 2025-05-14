#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

class Component;
class ConnectionPoint;
class Wire;

class Canvas : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Canvas(QObject *parent = nullptr);
    ~Canvas() override;
    
    void addComponent(Component* component);
    void removeComponent(Component* component);
    
    // Wire creation methods
    void startWireCreation(ConnectionPoint* startPoint);
    void completeWireCreation(ConnectionPoint* endPoint);
    void cancelWireCreation();
    
    // Add setView method
    void setView(QGraphicsView* view) { m_view = view; }

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QList<Component*> m_components;
    QList<Wire*> m_wires;
    
    // Wire creation state
    bool m_creatingWire;
    ConnectionPoint* m_wireStartPoint;
    Wire* m_tempWire;
    
    // Store the view
    QGraphicsView* m_view;
};

#endif // CANVAS_H
