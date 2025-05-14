#include "newproject.h"
#include "andgate.h"
#include "inputitem.h"
#include "outputitem.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>

NewProject::NewProject(QWidget *parent) : QWidget(parent)
{
    // Setup UI
    setWindowTitle("Logic Gate Simulator");
    resize(800, 600);
    
    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create canvas and view
    canvas = new Canvas(this);
    view = new QGraphicsView(canvas, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    
    // Set the view in canvas
    canvas->setView(view);
    
    // Add view to layout
    mainLayout->addWidget(view);
    
    // Create toolbar with buttons
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    
    QPushButton *btnAndGate = new QPushButton("Add AND Gate", this);
    connect(btnAndGate, &QPushButton::clicked, this, &NewProject::on_btn_andgate_clicked);
    
    QPushButton *btnAddInput = new QPushButton("Add Input", this);
    connect(btnAddInput, &QPushButton::clicked, this, &NewProject::on_btn_addInput_clicked);
    
    QPushButton *btnAddOutput = new QPushButton("Add Output", this);
    connect(btnAddOutput, &QPushButton::clicked, this, &NewProject::on_btn_addOutput_clicked);
    
    toolbarLayout->addWidget(btnAndGate);
    toolbarLayout->addWidget(btnAddInput);
    toolbarLayout->addWidget(btnAddOutput);
    toolbarLayout->addStretch();
    
    mainLayout->addLayout(toolbarLayout);
    
    // Set image paths for input components
    activeImagePath = ":/images/assets/ip-active.png";  // Update with your actual path
    inactiveImagePath = ":/images/assets/ip-not_active.png";  // Update with your actual path
}

NewProject::~NewProject()
{
}

void NewProject::on_btn_andgate_clicked()
{
    AndGate *andGate = new AndGate(nullptr, this);
    andGate->setPos(200, 200);
    canvas->addComponent(andGate);
}

void NewProject::on_btn_addInput_clicked()
{
    InputItem *inputItem = new InputItem(activeImagePath, inactiveImagePath, nullptr, this);
    inputItem->setPos(100, 200);
    canvas->addComponent(inputItem);
}

void NewProject::on_btn_addOutput_clicked()
{
    OutputItem *output = new OutputItem(nullptr, this);
    output->setPos(300, 200);
    canvas->addComponent(output);
}
