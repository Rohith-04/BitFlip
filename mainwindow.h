#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>

class Canvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addAndGate();
    void addInputComponent();
    void addOutputComponent();
    void clearCanvas();

private:
    void createActions();
    void createToolBar();

    Canvas *m_canvas;
    QGraphicsView *m_view;
    QToolBar *m_toolBar;
    
    QAction *m_addAndGateAction;
    QAction *m_addInputAction;
    QAction *m_addOutputAction;
    QAction *m_clearAction;

    QString activeImagePath;
    QString inactiveImagePath;
};

#endif // MAINWINDOW_H
