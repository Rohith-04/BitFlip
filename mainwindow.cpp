#include "mainwindow.h"
#include "canvas.h"
#include "andgate.h"
#include "inputitem.h"
#include "outputitem.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("Logic Gate Simulator");
    resize(800, 600);
    
    // Create canvas and view
    m_canvas = new Canvas(this);
    m_view = new QGraphicsView(m_canvas, this);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setDragMode(QGraphicsView::RubberBandDrag);
    
    // Set the view as the central widget
    setCentralWidget(m_view);
    
    // Create actions and toolbar
    createActions();
    createToolBar();
    
    // Show a welcome message
    QMessageBox::information(this, "Welcome", 
        "Welcome to the Logic Gate Simulator!\n\n"
        "- Add components using the toolbar\n"
        "- Double-click on input components to toggle their state\n"
        "- Click and drag from a connection point to create wires\n"
        "- Press ESC to cancel wire creation");

    // Set image paths for input components
    activeImagePath = ":/images/assets/ip-active.png";  // Update with your actual path
    inactiveImagePath = ":/images/assets/ip-not_active.png";  // Update with your actual path
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    m_addAndGateAction = new QAction("Add AND Gate", this);
    connect(m_addAndGateAction, &QAction::triggered, this, &MainWindow::addAndGate);
    
    m_addInputAction = new QAction("Add Input", this);
    connect(m_addInputAction, &QAction::triggered, this, &MainWindow::addInputComponent);
    
    m_addOutputAction = new QAction("Add Output", this);
    connect(m_addOutputAction, &QAction::triggered, this, &MainWindow::addOutputComponent);
    
    m_clearAction = new QAction("Clear All", this);
    connect(m_clearAction, &QAction::triggered, this, &MainWindow::clearCanvas);
}

void MainWindow::createToolBar()
{
    m_toolBar = addToolBar("Components");
    m_toolBar->addAction(m_addAndGateAction);
    m_toolBar->addAction(m_addInputAction);
    m_toolBar->addAction(m_addOutputAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_clearAction);
}

void MainWindow::addAndGate()
{
    AndGate *gate = new AndGate();
    gate->setPos(200, 200);
    m_canvas->addComponent(gate);
}

void MainWindow::addInputComponent()
{
    // Create a new InputItem with nullptr as parent (the scene will be the parent)
    InputItem *input = new InputItem(activeImagePath, inactiveImagePath, nullptr, this);

    // Set the position on the canvas
    input->setPos(100, 200);

    // Add the component to the canvas
    m_canvas->addComponent(input);
}

void MainWindow::addOutputComponent()
{
    OutputItem *output = new OutputItem(nullptr, this);
    output->setPos(300, 200);
    m_canvas->addComponent(output);
}

void MainWindow::clearCanvas()
{
    // Ask for confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Clear Canvas", "Are you sure you want to clear the canvas?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        m_canvas->clear();
    }
}
