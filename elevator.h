#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QMainWindow>
#include<QObject>

/*
系统				电梯控制系统V2.0
编写时间		2021/1/29
编译环境		VS2017 X86 Debug模式  SDK:10.0.17763.0
作者				李照月
说明：			对比1.0系统，加入了门控系统
收获：			按阶段编程，省时省力，一步到位
*/

#include<Windows.h>
#include<stdio.h>
#include<string.h>
#define LEVEL 6//楼层
//门的状态
enum eDoorState
{
    OPEN=1,	//已打开
    CLOSE,		//门关闭
    LOCK,		//门上锁
    OPENING,	//开门中
    CLOSING,	//关门中
};

//电梯的状态
enum eElevatorState
{
    STOP=1,
    UP,
    DOWN
};

//门控状态
enum eDoorButton
{
    NONE=0,
    OPENDOOR,
    CLOSEDOOR
};

enum eElevatorDirection
{
    LIFT=1,
    DROP,
    SUSPEND
};

//电梯高度
struct ElevatorHight
{
    ElevatorHight():nowHight(0), levelHigh(1000)	,fullLevel(LEVEL)	, moveSpeed(5){}
    int nowHight;	//当前高度
    const int levelHigh;	//每层楼高度
    const int fullLevel;		//总楼层
    const int moveSpeed;
};

//电梯宽度
struct DoorWidth
{
    DoorWidth() :nowWidth(0), fullWidth(1000),openSpeed(5),waitTime(100){}
    int nowWidth;
    const int fullWidth ;
    const int openSpeed ;
    const int waitTime;
};

//电梯类编写
class Elevator : public QObject
{
public: //属性
    char floorDownList[LEVEL];		//楼层下行按钮
    char floorUpList[LEVEL];			//楼层上行按钮
    char panelButtonList[LEVEL];	//电梯内面板楼层按钮

    enum eDoorState doorState;	//门的状态
    enum eElevatorState elevatorState;		//电梯状态
    enum eDoorButton doorButton;			//门控按钮
    enum eElevatorDirection liftDirection;	//电梯的运行方向


    struct ElevatorHight elevatorHight;	//电梯高度
    struct DoorWidth  doorWidth;			//门的宽度

    Elevator();
private://行为
    void doorClose();	//门关闭
    void doorLock();		//门上锁
    void doorOpening();	//门开机
    void doorClosing();		//门关闭
    void doorOpen();		//门打开

    void liftStop();
    void liftUp();
    void liftDown();

private: //线程
    static DWORD WINAPI doorThread(void* p);				//门线程
    static DWORD WINAPI elevatorThread(void* p);		//电梯线程

};

#endif // ELEVATOR_H
