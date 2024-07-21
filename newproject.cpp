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

NewProject::NewProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NewProject)
{
    ui->setupUi(this);
    showMaximized();
    canvas = new Canvas(this);
    view = new QGraphicsView(canvas, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);

    btnAddAndGate = new QPushButton("Add AND Gate", this);
    btnAddInput = new QPushButton("Add Input", this);

    connect(btnAddAndGate, &QPushButton::clicked, this, &NewProject::on_btn_andgate_clicked);
    connect(btnAddInput, &QPushButton::clicked, this, &NewProject::on_btn_addInput_clicked);

    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // Add widgets to layouts
    buttonLayout->addWidget(btnAddAndGate);
    buttonLayout->addWidget(btnAddInput);
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
    QString activeImagePath = ":/ip-active.png";
    QString inactiveImagePath = ":/ip-not_active.png";
    InputItem *inputItem = new InputItem(activeImagePath, inactiveImagePath);
    inputItem->setFlag(QGraphicsItem::ItemIsMovable);
    inputItem->setFlag(QGraphicsItem::ItemIsSelectable);
    canvas->addComponent(inputItem);
    inputItem->setPos(100, 100);
}
