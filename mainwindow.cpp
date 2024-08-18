#include <QEvent>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newproject.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set up the image label
    imageLabel = new QLabel(this);
    imageLabel->setGeometry(50, 50, 200, 200);

    // Load static image
    staticImage = QPixmap(":/images/assets/still_image.png");
    imageLabel->setPixmap(staticImage);

    // Prepare GIF
    gifMovie = new QMovie(":/images/assets/logo.gif");

    // Install event filter on central widget
    ui->centralwidget->setMouseTracking(true);
    ui->centralwidget->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    //Destructing the new project window will be handled automatically as the main window is the parent

    delete gifMovie;
}

void MainWindow::on_btn_newProject_clicked() {
    ptr_newProject = new NewProject(this); //Creating the New Project window in the constructor

    //Closes even the main window when the new project window is closed
    connect(ptr_newProject, &NewProject::closed, this, [this]() {
            this->show(); // Show MainWindow when NewProject is destroyed
            qDebug() << "Showing Main Window";
        });
    ptr_newProject->show();
    this->hide();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->centralwidget) {
        if (event->type() == QEvent::Enter) {
            imageLabel->setMovie(gifMovie);
            gifMovie->start();
        } else if (event->type() == QEvent::Leave) {
            gifMovie->stop();
            imageLabel->setPixmap(staticImage);
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
