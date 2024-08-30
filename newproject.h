#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPushButton>
#include <QHBoxLayout>
#include "canvas.h"
#include "andgate.h"
#include "inputitem.h"
#include "outputitem.h"

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
    Canvas* getCanvas();

private slots:
    void on_btn_andgate_clicked();
    void on_btn_addInput_clicked();
    void on_btn_addOutput_clicked();

signals:
    void closed();
private:
    Ui::NewProject *ui;
    void closeEvent(QCloseEvent *event);
    QGraphicsView *view;
    Canvas *canvas;
    QPushButton *btnAddAndGate;
    QPushButton *btnAddInput;
    QPushButton *btnAddOutput;
    QList<QGraphicsItem*> inputItems;
    QList<QGraphicsItem*> outputItems;
};

#endif // NEWPROJECT_H
