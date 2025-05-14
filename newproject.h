#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QWidget>
#include <QGraphicsView>
#include "canvas.h"

class NewProject : public QWidget
{
    Q_OBJECT

public:
    explicit NewProject(QWidget *parent = nullptr);
    ~NewProject();

private slots:
    void on_btn_andgate_clicked();
    void on_btn_addInput_clicked();
    void on_btn_addOutput_clicked();

private:
    Canvas *canvas;
    QGraphicsView *view;
    
    QString activeImagePath;
    QString inactiveImagePath;
};

#endif // NEWPROJECT_H
