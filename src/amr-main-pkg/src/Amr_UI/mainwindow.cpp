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
    frame3Size = ui->frame_3->size();
    textEdit_2Size = ui->textEdit_2->size();
    scaling_x = frameSize.width()/20;
    scaling_y = frameSize.height()/20;

    scaling_x_obs = frameSize.width()/100;
    scaling_y_obs = frameSize.height()/100;

    add_x = ui->frame->x()+frameSize.width()/2;
    add_y = ui->frame->y()+frameSize.height()/2;

    add_x_obs = ui->frame->x();
    add_y_obs = ui->frame->y()+frameSize.height();

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
    painter.setRenderHint(QPainter::Antialiasing);

    drawcoordinates(painter);

    pen.setColor(Qt::blue);
    pen.setWidth(1);
    painter.setPen(pen);

    for (int i=2;i<points.size();i++)
    {
        painter.drawLine(points[i-1],points[i]);
    }

    pen.setColor(Qt::blue);
    pen.setWidth(5);
    painter.setPen(pen);

    painter.drawPoint(points2.first()); // obstacle's center point plot

    pen.setWidth(1);
    painter.setPen(pen);

    for(const QPoint& point : dotDataset)
    {
        painter.drawPoint(point); // obstacle's Chassis points
    }

}


void MainWindow::updatePoints()
{
    QPoint newPoint((sharedMemory->xpos)*scaling_x+add_x, (sharedMemory->ypos)*(-scaling_y)+add_y); // 임의의 점 생성
    QPoint newPoint2((sharedMemory->Dynamicobstacle_x)*scaling_x_obs+add_x_obs, (sharedMemory->Dynamicobstacle_y)*(-scaling_y_obs)+add_y_obs);

    points.append(newPoint);
    points2.clear();
    points2.append(newPoint2);

    update();
}

void MainWindow::updateDotDataset()
{
    dotDataset.clear();

    for(int i = 0; i < dynamicSharedMemory.Clustered_point.size(); i++){
        QPoint newDataPoint((dynamicSharedMemory.Clustered_point[i].x)*scaling_x+add_x,(dynamicSharedMemory.Clustered_point[i].y)*(-scaling_y)+add_y);
        dotDataset.append(newDataPoint);
    }

    update();
}


void MainWindow::drawcoordinates(QPainter& painter)
{
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);

    // x 축 그리기 (가로선)
    painter.drawLine(ui->frame->x(), ui->frame->y()+frameSize.height()/2, ui->frame->x()+(frameSize.width()), (frameSize.height())/2 + ui->frame->y());
    painter.drawLine(ui->frame_3->x(), ui->frame_3->y()+(frame3Size.height()+textEdit_2Size.height())/2, ui->frame_3->x()+frame3Size.width(), ui->frame_3->y()+(frame3Size.height()+textEdit_2Size.height())/2);

    // y 축 그리기 (세로선)
    painter.drawLine(ui->frame->x()+frameSize.width()/2, ui->frame->y(), ui->frame->x()+frameSize.width()/2, ui->frame->y()+frameSize.height());
    painter.drawLine(ui->frame_3->x()+frame3Size.width()/2, ui->frame_3->y()+textEdit_2Size.height()/2, ui->frame_3->x()+frame3Size.width()/2, ui->frame_3->y()+frame3Size.height());

    for(int i=1;i<20;i++)
    {
        //x축 좌표 그리기
        painter.drawLine(ui->frame->x()+(frameSize.width()/20)*i,ui->frame->y()+frameSize.height()/2-2,ui->frame->x()+(frameSize.width()/20)*i,ui->frame->y()+frameSize.height()/2+2);
        painter.drawLine(ui->frame_3->x()+(frame3Size.width()/20)*i,ui->frame_3->y()+(frame3Size.height()+textEdit_2Size.height())/2-2,ui->frame_3->x()+(frame3Size.width()/20)*i,ui->frame_3->y()+(frame3Size.height()+textEdit_2Size.height())/2+2);
        painter.drawLine(ui->frame->x()+frameSize.width()/2-2,ui->frame->y()+frameSize.height()/20*i,ui->frame->x()+frameSize.width()/2+2,ui->frame->y()+frameSize.height()/20*i);
        painter.drawLine(ui->frame_3->x()+frame3Size.width()/2-2,ui->frame_3->y()+(frame3Size.height()-textEdit_2Size.height())/20*i+30,ui->frame_3->x()+frame3Size.width()/2+2,ui->frame_3->y()+(frame3Size.height()-textEdit_2Size.height())/20*i+30);
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
    QString labelText = "AMR 현재위치: ( " + QString::number(sharedMemory->xpos) + ", " + QString::number(sharedMemory->ypos) + ")";
    QString labelText_2 = "Obstacle 현재위치: ( " + QString::number(sharedMemory->Dynamicobstacle_x/5-10) + ", " + QString::number(sharedMemory->Dynamicobstacle_y/5-10) + ")";
    ui->label->setText(labelText);
    ui->label_2->setText(labelText_2);
}





