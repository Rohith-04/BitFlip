#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "newproject.h"
#include "ui_newproject.h"
#include "canvas.h"
#include "andgate.h"
#include "inputitem.h"
#include "outputitem.h"

NewProject::NewProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NewProject)
{
    ui->setupUi(this);
    showMaximized();
    canvas = new Canvas(this);
    canvas->setBackgroundBrush(Qt::lightGray);
    view = new QGraphicsView(canvas, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    canvas->setView(view);

    btnAddAndGate = new QPushButton("Add AND Gate", this);
    btnAddInput = new QPushButton("Add Input", this);
    btnAddOutput = new QPushButton("Add Output", this);

    connect(btnAddAndGate, &QPushButton::clicked, this, &NewProject::on_btn_andgate_clicked);
    connect(btnAddInput, &QPushButton::clicked, this, &NewProject::on_btn_addInput_clicked);
    connect(btnAddOutput, &QPushButton::clicked, this, &NewProject::on_btn_addOutput_clicked);

    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Add widgets to layouts
    buttonLayout->addWidget(btnAddAndGate);
    buttonLayout->addWidget(btnAddInput);
    buttonLayout->addWidget(btnAddOutput);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(view);

    // Create a central widget and set layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

NewProject::~NewProject() {
    delete ui;
}

void NewProject::on_btn_andgate_clicked() {
    qDebug() << "Adding AND Gate";
    AndGate *andGate = new AndGate();
    andGate->setFlag(QGraphicsItem::ItemIsMovable);
    andGate->setFlag(QGraphicsItem::ItemIsSelectable);
    canvas->addComponent(andGate);
    andGate->setPos(100, 100);
}

void NewProject::on_btn_addInput_clicked() {
    qDebug() << "Adding Input Item";
    QString activeImagePath = ":images/assets/ip-active.png";
    QString inactiveImagePath = ":images/assets/ip-not_active.png";
    InputItem *inputItem = new InputItem(activeImagePath, inactiveImagePath);
    inputItem->setFlag(QGraphicsItem::ItemIsMovable);
    inputItem->setFlag(QGraphicsItem::ItemIsSelectable);
    canvas->addComponent(inputItem);
    inputItem->setPos(100, 100);
}

void NewProject::on_btn_addOutput_clicked() {
    qDebug() << "Adding output item";
    QString activeOpImagePath = ":/images/assets/op-active.png";
    QString inactiveOpImagePath = ":/images/assets/op-not_active.png";
    OutputItem *outputItem = new OutputItem(activeOpImagePath,inactiveOpImagePath);
    outputItem->setFlag(QGraphicsItem::ItemIsMovable);
    outputItem->setFlag(QGraphicsItem::ItemIsSelectable);
    canvas->addComponent(outputItem);
    outputItem->setPos(20,20);
}
