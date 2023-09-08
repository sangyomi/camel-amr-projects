//
// Created by dongju on 23. 9. 7.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulmain/simul_main.hpp"
#include "../../include/Variables/SharedMemory.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); //생성자
    ~MainWindow(); //소멸자

private slots:
    void updateScene();
    void drawRectangular();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QTimer *timer;
    QVector<QPointF> points; // coordinates storage
    QPen pen; //line style
    int radius;

};

#endif // MAINWINDOW_H

