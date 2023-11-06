//
// Created by dongju on 23. 9. 7.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"


extern pSHM sharedMemory;
extern DSHM dynamicSharedMemory;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    frameSize = ui->frame->size();
    scaling_x = frameSize.width()/20;
    scaling_y = frameSize.height()/20;

    add_x = ui->frame->x()+frameSize.width()/2;
    add_y = ui->frame->y()+frameSize.height()/2;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePoints()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDotDataset()));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateLabel()));
    timer->start(100);
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPainter painter2(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter2.setRenderHint(QPainter::Antialiasing);

    drawcoordinates(painter);



    pen.setColor(Qt::blue);  // 파란색으로 점 그리기

    pen.setWidth(2);
    painter.setPen(pen);


    for (int i=2;i<points.size();i++)
    {
        painter.drawLine(points[i-1],points[i]);
    }


    painter.drawPoint(points2.first());

    for(const QPoint& point : dotDataset)
    {
        painter.setPen(Qt::red);
        painter.drawPoint(point);
    }


}


void MainWindow::updatePoints()
{

//    QPoint newPoint((sharedMemory->xpos)*scaling_x+add_x, (sharedMemory->ypos)*(-scaling_y)+add_y); // 임의의 점 생성
    QPoint newPoint((sharedMemory->Dynamicobstacle_y)*scaling_x+add_x, (sharedMemory->Dynamicobstacle_x)*(-scaling_y)+add_y); // 임의의 점 생성
    QPoint newPoint2((sharedMemory->Dynamicobstacle_x)*scaling_x+add_x, (sharedMemory->Dynamicobstacle_y)*(-scaling_y)+add_y);



    points.append(newPoint);

    points2.clear();
    points2.append(newPoint2);



    update();
}

void MainWindow::updateDotDataset()
{
    for(int i = 0; i < dynamicSharedMemory.Clustered_point.size(); i++){
        QPoint newDataPoint((dynamicSharedMemory.Clustered_point[i].x)*scaling_x+add_x,(dynamicSharedMemory.Clustered_point[i].y)*(-scaling_y)+add_y);
        dotDataset.append(newDataPoint);
    }


    update();


}


void MainWindow::drawcoordinates(QPainter& painter)
{
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);

    // x 축 그리기 (가로선)
    painter.drawLine(ui->frame->x(), ui->frame->y()+frameSize.height()/2, ui->frame->x()+(frameSize.width()), (frameSize.height())/2 + ui->frame->y());


    // y 축 그리기 (세로선)
    painter.drawLine(ui->frame->x()+frameSize.width()/2, ui->frame->y(), ui->frame->x()+frameSize.width()/2, ui->frame->y()+frameSize.height());


    for(int i=1;i<20;i++)
    {
        //x축 좌표 그리기
        painter.drawLine(ui->frame->x()+(frameSize.width()/20)*i,ui->frame->y()+frameSize.height()/2-2,ui->frame->x()+(frameSize.width()/20)*i,ui->frame->y()+frameSize.height()/2+2);
        painter.drawLine(ui->frame->x()+frameSize.width()/2-2,ui->frame->y()+frameSize.height()/20*i,ui->frame->x()+frameSize.width()/2+2,ui->frame->y()+frameSize.height()/20*i);

    }


}


MainWindow::~MainWindow()
{

    delete timer;
    delete ui;
    free(sharedMemory);
}



void MainWindow::updateLabel()
{

//    QString labelText = "AMR 현재위치: ( " + QString::number(sharedMemory->xpos) + ", " + QString::number(sharedMemory->ypos) + ")";
    QString labelText = "AMR 현재위치: ( " + QString::number(sharedMemory->Dynamicobstacle_x) + ", " + QString::number(sharedMemory->Dynamicobstacle_y) + ")";
    ui->label->setText(labelText);
}





