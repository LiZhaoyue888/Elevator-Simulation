/*文件：       电梯控制系统 Qt5适配层
 *作用：       电梯状态显示+电梯状态控制
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<windows.h>
#include"elevator.h"
#include<QPushButton>

#include<QDebug>

Elevator *globalElevator;

extern QPushButton *leftDoorBtn;
extern QPushButton *rightDoorBtn;
extern QPushButton *elevatorBtn;
MainWindow * uiMainWindow;

#include <QApplication>

DWORD WINAPI startElevator(void *p)
{
    Elevator* e = new Elevator();
    globalElevator = e;

    Sleep(10);

    while (true)
    {
        emit elevatorBtn->clicked();
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI syncDoorWidth(void *p)
{
    int width;

    while(true)
    {
        width = globalElevator->doorWidth.nowWidth;
        if(width!=0)
        {
            //发送信号
            emit leftDoorBtn->clicked();
            emit rightDoorBtn->clicked();
            Sleep(10);
        }
        Sleep(50);
    }
    return 0;
}

