#include "newproject.h"
#include "ui_newproject.h"

NewProject::NewProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NewProject)
{
    ui->setupUi(this);
    showMaximized();
    canvas = new Canvas(this);
    canvas->setBackgroundBrush(QColor(71,73,77,255));
    view = new QGraphicsView(canvas, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    canvas->setView(view);

    btnAddInput = new QPushButton("Add Input", this);
    btnAddAndGate = new QPushButton("Add AND Gate", this);
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
/*
    InputItem *ip1 = new InputItem(":images/assets/ip-active.png", ":images/assets/ip-not_active.png");
    InputItem *ip2 = new InputItem(":images/assets/ip-active.png", ":images/assets/ip-not_active.png");
    OutputItem *op = new OutputItem(":images/assets/op-active.png", ":images/assets/op-not_active.png");
    canvas->addComponent(ip1);
    canvas->addComponent(ip2);
    canvas->addComponent(op);
    canvas->repositionItems();
*/

}

void NewProject::closeEvent(QCloseEvent *event){
    emit closed();
    QWidget::closeEvent(event);
}

NewProject::~NewProject() {
    delete ui;
    qDebug() << "New Project Window is destroyed";
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
    canvas->addComponent(inputItem);
}

void NewProject::on_btn_addOutput_clicked() {
    qDebug() << "Adding output item";
    QString activeOpImagePath = ":/images/assets/op-active.png";
    QString inactiveOpImagePath = ":/images/assets/op-not_active.png";
    OutputItem *outputItem = new OutputItem(activeOpImagePath, inactiveOpImagePath);
    canvas->addComponent(outputItem);
}
