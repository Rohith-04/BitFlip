#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newproject.h"

//Forward declaration of New Project
class NewProject;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_newProject_clicked();

private:
    Ui::MainWindow *ui;
    NewProject *ptr_newProject;
};
#endif // MAINWINDOW_H
