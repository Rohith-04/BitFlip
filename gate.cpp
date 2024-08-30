#include "gate.h"

Gate::Gate(QGraphicsItem *parent,NewProject *project) : Component(parent), m_project(project) {
    qDebug() << "Gate const is called";
    firstInput = false;
    secondInput = false;
    output = false;
    input1 = nullptr;
    input2 = nullptr;
    outputPoint = nullptr;
    qDebug() << "Gate: ---" << m_project;
}

void Gate::initConnectionPoints(){
    input1 = new ConnectionPoint(this,m_project);
    input2 = new ConnectionPoint(this,m_project);
    outputPoint = new ConnectionPoint(this,m_project);
    updateConnectionPoints();
}

void Gate::updateConnectionPoints(){
    QList<QPointF> connectionPoints = getConnectionPoints();
    //float r = input1->getRadius();

    input1->setPos(connectionPoints[0].x(), connectionPoints[0].y());
    input2->setPos(connectionPoints[1].x(), connectionPoints[1].y());
    outputPoint->setPos(connectionPoints[2].x(), connectionPoints[2].y());
}

QRectF Gate::boundingRect() const{
    return QRectF(0 , 0 , m_pixmap.width(), m_pixmap.height());
}

QList<QPointF> Gate::getConnectionPoints() {
    QList<QPointF> points;
    QRectF bounds = boundingRect();

    points << QPointF(static_cast<float>(bounds.left()), static_cast<float>(bounds.top()) + static_cast<float>(bounds.height()) * 0.25);
    points << QPointF(static_cast<float>(bounds.left()), static_cast<float>(bounds.top()) + static_cast<float>(bounds.height()) * 0.75);
    points << QPointF(static_cast<float>(bounds.right()), static_cast<float>(bounds.top()) + static_cast<float>(bounds.height()) * 0.5);

    return points;
}

//Mouse Handling Functions

void Gate::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "Gate Press Event";
    Component::mousePressEvent(event);
}

void Gate::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //qDebug() << "Gate is moving";
    Component::mouseMoveEvent(event);
}

void Gate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //qDebug() << "Gate is released";
    Component::mouseReleaseEvent(event);
}

void Gate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        qDebug() << "Removing Gate";
        if(scene()){
            scene()->removeItem(this);
        }
        delete this;
    }
}

//Setters
void Gate::setFirstInput(bool val){
    firstInput = val;
}

void Gate::setSecondInput(bool val){
    secondInput = val;
}

void Gate::setOutput(bool val){
    output = val;
}

//Getters
bool Gate::getFirstInput(){
    return firstInput;
}

bool Gate::getSecondInput(){
    return secondInput;
}

bool Gate::getOutput(){
    return output;
}

