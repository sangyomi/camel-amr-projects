//
// Created by dongju on 23. 9. 7.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"


extern pSHM sharedMemory;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 그래픽 뷰 생성 및 설정
    ui->Textedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Textedit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view = new QGraphicsView(ui->frame);
    view2 = new QGraphicsView(ui->frame_2);
    scene = new QGraphicsScene(this);
    view->setScene(scene);

    // 그래픽 뷰 탭1 생성 및 설정
//    view->setGeometry(ui->frame->rect());
    view->setSceneRect(12,39,698,698);
    view->setRenderHint(QPainter::Antialiasing);

    view2->setGeometry(ui->frame_2->rect());



    // 선을 그릴 QPen 설정
    pen.setColor(Qt::red);
    pen.setWidth(1);

    // 타이머 생성 및 설정
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateScene);
    timer->start(500); // 1000ms마다 새로운 점 추가
}

MainWindow::~MainWindow()
{
    delete view; //delte dynamic allocation
    delete scene;
    delete timer;
    delete ui;
    free(sharedMemory);
}

void MainWindow::updateScene()
{
    int circumstance =8;
    QPointF newPoint((sharedMemory->xpos)*35+360, (sharedMemory->ypos)*(-35)+390); // 임의의 점 생성(-200~200)
    points.append(newPoint);

    // 씬에 점을 추가
    scene->clear(); //delete previous point
    scene->addEllipse(newPoint.x() - circumstance/2, newPoint.y() - circumstance/2, circumstance, circumstance, pen);

    // 선을 그립니다.
    if (points.size() >= 2) {
        for (int i = 2; i < points.size(); ++i) {
            scene->addLine(QLineF(points[i - 1], points[i]), pen);
        }
    }
}






