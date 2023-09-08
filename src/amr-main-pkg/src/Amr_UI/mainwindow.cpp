//
// Created by dongju on 23. 9. 7.
//

#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include <QTimer>


extern pSHM sharedMemory;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{

    // 그래픽 뷰 생성 및 설정
    view = new QGraphicsView(this);
    setCentralWidget(view);

    // 그래픽 씬 생성
    scene = new QGraphicsScene(this);
    view->setScene(scene);

    resize(800,800);
    // 그래픽 뷰 설정
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setRenderHint(QPainter::Antialiasing);
//    view->setSceneRect(200, 200, 400, 400);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // 선을 그릴 QPen 설정
    pen.setColor(Qt::red);
    pen.setWidth(1);

    // 타이머 생성 및 설정
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateScene);
    timer->start(500); // 1000ms마다 새로운 점 추가
    connect(timer, &QTimer::timeout, this, &MainWindow::drawRectangular);
}

MainWindow::~MainWindow()
{
    delete view; //delte dynamic allocation
    delete scene;
    delete timer;
    free(sharedMemory);
}

void MainWindow::updateScene()
{
    radius =8;
    QPointF newPoint((sharedMemory->xpos)*20, (sharedMemory->ypos)*(-20)); // 임의의 점 생성(-200~200)
    points.append(newPoint);

    // 씬에 점을 추가
    scene->clear(); //delete previous point
    scene->addEllipse(newPoint.x() - radius/2, newPoint.y() - radius/2, radius, radius, pen);

    // 선을 그립니다.
    if (points.size() >= 2) {
        for (int i = 2; i < points.size(); ++i) {
            scene->addLine(QLineF(points[i - 1], points[i]), pen);
        }
    }
}


void MainWindow::drawRectangular(){
    QGraphicsRectItem *rectangle = new QGraphicsRectItem(-200,-200,400,400);

    QPen pen1;
    pen1.setColor(Qt::black);
    pen1.setWidth(2);
    rectangle->setPen(pen1);
    scene->addItem(rectangle);


}




