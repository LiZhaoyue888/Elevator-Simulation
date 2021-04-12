#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<windows.h>
#include"elevator.h"
#include<QDebug>

//
extern Elevator* globalElevator;

QPushButton *leftDoorBtn;
QPushButton *rightDoorBtn;
QPushButton *elevatorBtn;

extern MainWindow * uiMainWindow;
//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_leftDoor_clicked()
{
    int width = globalElevator->doorWidth.nowWidth / 10;
    leftDoorBtn->setGeometry(50, 40, 101-width, 200);
}

void MainWindow::on_rightDoor_clicked()
{
    int width = globalElevator->doorWidth.nowWidth / 10;
    rightDoorBtn->setGeometry(150+width, 40, 101-width, 200);
}



void MainWindow::on_pushButton_clicked()
{

}


DWORD WINAPI startElevator(void *p);
DWORD WINAPI syncDoorWidth(void *p);


void MainWindow::on_startBtn_clicked()
{
    CreateThread(NULL,0,startElevator,NULL,0,NULL);

    leftDoorBtn = ui->leftDoor;
    rightDoorBtn = ui->rightDoor;
    elevatorBtn = ui->elevatorButton;

    Sleep(100);

    ele = globalElevator;

    CreateThread(NULL,0,syncDoorWidth,NULL,0,NULL);

    ui->startBtn->setDisabled(true);
}

void MainWindow::on_elevatorButton_clicked() //电梯
{
    int hight;
    hight = globalElevator->elevatorHight.nowHight / 10;
    ui->elevatorButton->move(300,550-hight);
    int level = globalElevator->elevatorHight.nowHight / globalElevator->elevatorHight.levelHigh+1;

    ui->lcdNumber->display(level);
}

void MainWindow::on_pushButton_14_clicked() //开门
{
    if(globalElevator->elevatorState != STOP){
        return ;
    }

    if(globalElevator->doorState == OPEN){
        return;
    }

    globalElevator->doorButton = OPENDOOR;
}

void MainWindow::on_pushButton_15_clicked() //关门
{
    if(globalElevator->elevatorState != STOP){
        return ;
    }

   globalElevator->doorButton = CLOSEDOOR;
}

void MainWindow::on_btn_l1_clicked()
{
    globalElevator->panelButtonList[0]=1;
}

void MainWindow::on_btn_l2_clicked()
{
    globalElevator->panelButtonList[1]=1;
}

void MainWindow::on_btn_l3_clicked()
{
    globalElevator->panelButtonList[2]=1;
}

void MainWindow::on_btn_l4_clicked()
{
    globalElevator->panelButtonList[3]=1;
}

void MainWindow::on_btn_l5_clicked()
{
    globalElevator->panelButtonList[4]=1;
}

void MainWindow::on_btn_l6_clicked()
{
    globalElevator->panelButtonList[5]=1;
}

void MainWindow::on_pushButton_7_clicked()
{
    globalElevator->floorDownList[5]=1;
}

void MainWindow::on_pushButton_6_clicked()
{
    globalElevator->floorUpList[4]=1;
}

void MainWindow::on_pushButton_5_clicked()
{
    globalElevator->floorDownList[4]=1;
}

void MainWindow::on_pushButton_8_clicked()
{
    globalElevator->floorUpList[3]=1;
}

void MainWindow::on_pushButton_9_clicked()
{
    globalElevator->floorDownList[3]=1;
}

void MainWindow::on_pushButton_10_clicked()
{
    globalElevator->floorUpList[2]=1;
}

void MainWindow::on_pushButton_11_clicked()
{
   globalElevator->floorDownList[2]=1;
}

void MainWindow::on_pushButton_12_clicked()
{
    globalElevator->floorUpList[1]=1;
}

void MainWindow::on_pushButton_13_clicked()
{
    globalElevator->floorDownList[1]=1;
}

void MainWindow::on_pushButton_16_clicked()
{
    globalElevator->floorUpList[0]=1;
}

void MainWindow::on_pushButton_17_clicked()
{
    for (int i = 0; i < LEVEL; i++)
    {
        globalElevator->panelButtonList[i] = 1;
    }
    for (int i = 0; i < LEVEL-1; i++)
    {
        globalElevator->floorUpList[i] = 1;
    }
    for (int i =1; i < LEVEL ; i++)
    {
        globalElevator->floorDownList[i] = 1;
    }
}
