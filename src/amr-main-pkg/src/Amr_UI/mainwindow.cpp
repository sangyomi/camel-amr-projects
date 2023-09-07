//
// Created by dongju on 23. 9. 7.
//

#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include <QTimer>


extern pSHM sharedMemory;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QTimer를 사용하여 주기적으로 값을 업데이트
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start(100); // 100 밀리초마다 타이머 호출

}

MainWindow::~MainWindow()
{
    delete ui;
    free(sharedMemory);
}

void MainWindow::updateValue()
{
    double randomValue = sharedMemory->xpos;
    ui->label->setText(QString("바뀐 값: %1").arg(randomValue));
}



