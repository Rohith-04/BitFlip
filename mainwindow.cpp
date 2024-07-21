#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newproject.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
}

MainWindow::~MainWindow()
{
    delete ui;
    //Destructing the new project window will be handled automatically as the main window is the parent
}

void MainWindow::on_btn_newProject_clicked() {
    ptr_newProject = new NewProject(this); //Creating the New Project window in the constructor
    ptr_newProject->show();
    this->hide(); //So that if the user wants to go to homepage he can do it using the button instead of killing the window
}

