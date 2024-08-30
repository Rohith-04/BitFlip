#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMovie>
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
    bool eventFilter(QObject *obj, QEvent *event) override;
    NewProject *ptr_newProject;

private slots:

    void on_btn_newProject_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QPixmap staticImage;
    QMovie *gifMovie;
};
#endif // MAINWINDOW_H
