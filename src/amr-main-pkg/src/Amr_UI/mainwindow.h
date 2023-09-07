//
// Created by dongju on 23. 9. 7.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulmain/simul_main.hpp"
#include "../../include/Variables/SharedMemory.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
            void updateValue(); // 값 업데이트 슬롯

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

