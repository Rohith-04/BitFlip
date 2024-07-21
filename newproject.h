#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include "canvas.h"

namespace Ui {
class NewProject;
}

class Canvas;

class NewProject : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewProject(QWidget *parent = nullptr);
    ~NewProject();

private slots:
    void on_btn_andgate_clicked();
    void on_btn_addInput_clicked();

private:
    Ui::NewProject *ui;
    QGraphicsView *view;
    Canvas *canvas;
    QPushButton *btnAddAndGate;
    QPushButton *btnAddInput;
};

#endif // NEWPROJECT_H
