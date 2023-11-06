//
// Created by dongju on 23. 9. 7.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulmain/simul_main.hpp"
#include "../../include/Variables/SharedMemory.h"
#include <QTimer>
#include <QPen>
#include <QVector>
#include <QPoint>
#include <QLabel>
#include <QPainter>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); //생성자
    ~MainWindow(); //소멸자

public:
    void paintEvent(QPaintEvent* event);
    void drawcoordinates(QPainter &painter);

private slots:
    void updatePoints();
    void updateLabel();
    void updateDotDataset();


private:
    Ui::MainWindow *ui;
    QPen pen; //line style
    QTimer* timer;
    QVector<QPoint> points;
    QVector<QPoint> points2;
    QVector<QPoint> dotDataset;
    QLabel* label;
    QSize frameSize;
    double scaling_x;
    double scaling_y;
    double add_x, add_y;


};

#endif // MAINWINDOW_H

