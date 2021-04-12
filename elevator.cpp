/*
 *文件                    电梯状态机
 * 版本：                  v2.2
 *最后修改日期：            2021/2/4
 *
*/

#include "elevator.h"
#include<QDebug>

#define HZ 10			//10HZ刷新速度

Elevator::Elevator()
{
    doorButton = NONE;
    doorState = CLOSE;
    elevatorState = STOP;
    liftDirection = SUSPEND;

    doorWidth.nowWidth = 0;
    elevatorHight.nowHight = 0;

    memset(floorDownList, 0, sizeof(floorDownList));
    memset(floorUpList, 0, sizeof(floorUpList));
    memset(panelButtonList, 0, sizeof(panelButtonList));

    CreateThread(NULL, 0, doorThread, this, 0, NULL);
    CreateThread(NULL, 0, elevatorThread, this, 0, NULL);
}

//门关闭态函数
void Elevator::doorClose()
{
    while (doorState == CLOSE)
    {
        if (doorButton == OPENDOOR)
        {
            doorState = OPENING;
            return;
        }

        if ((elevatorState == UP) || (elevatorState == DOWN))
        {
            doorState = LOCK;
            return;
        }

        if (doorButton == CLOSEDOOR)
        {
            doorButton = NONE;
        }

        Sleep(HZ);
    }
}

//门上锁
void Elevator::doorLock()
{
    while (true)
    {
        if (elevatorState == STOP)
        {
            doorState = OPENING;
            return;
        }
        Sleep(HZ);
    }
}

void Elevator::doorOpening()	//门开了
{
    while (true)
    {
        if (doorWidth.nowWidth < doorWidth.fullWidth)
        {
            doorWidth.nowWidth += doorWidth.openSpeed;
        }
        if (doorWidth.nowWidth == doorWidth.fullWidth)
        {
            if (doorButton == OPENDOOR)
                doorButton = NONE;
            doorState = OPEN;
            return;
        }

        if (doorButton == CLOSEDOOR)
        {
            doorState = CLOSING;
            return;
        }

        Sleep(HZ);
    }
}

void Elevator::doorClosing()		//门关闭
{
    while (true)
    {
        if (doorState == CLOSING)
        {
            doorWidth.nowWidth -= doorWidth.openSpeed;
        }

        if (doorWidth.nowWidth == 0)
        {
            doorState = CLOSE;
            return;
        }

        if (doorButton == OPENDOOR)
        {
            doorState = OPENING;
            return;
        }

        Sleep(HZ);
    }
}

void Elevator::doorOpen()		//门打开
{
    int	 delay = doorWidth.waitTime;
    while (delay > 0)
    {
        if (doorButton == CLOSEDOOR)
        {
            doorState = CLOSING;
            return;
        }
        if (doorButton == OPENDOOR)
        {
            delay = doorWidth.waitTime;
            continue;
        }
        delay--;
        Sleep(HZ);
    }
    doorState = CLOSING;
    if (doorButton == OPENDOOR)
    {
        doorButton = NONE;
    }
}

//门控线程
DWORD WINAPI Elevator::doorThread(void* p)
{
    Elevator *elevator = (Elevator*)p;

    while (true)
    {
        switch (elevator->doorState)
        {
        case CLOSE:
            elevator->doorClose();
            break;
        case LOCK:
            elevator->doorLock();
            break;
        case OPENING:
            elevator->doorOpening();
            break;
        case CLOSING:
            elevator->doorClosing();
            break;
        case OPEN:
            elevator->doorOpen();
            break;
        }
        Sleep(1);
    }

    return 0;
}

void Elevator::liftDown()
{
    int level;
    do {
        elevatorHight.nowHight -= elevatorHight.moveSpeed;
        level = elevatorHight.nowHight / elevatorHight.levelHigh;

        int i;
        for (i = level; i >0; i--)			//检测目的楼层
        {
            if ((floorDownList[level] == 1) || (panelButtonList[level] == 1))
            {
                break;
            }
        }

        if (elevatorHight.nowHight % elevatorHight.levelHigh == 0)		//有信号，则停止
        {
            if ((floorDownList[level] == 1) || (panelButtonList[level] == 1))
            {
                floorDownList[level] = 0;
                panelButtonList[level] = 0;

                elevatorState = STOP;
                return;
            }
            if (i == elevatorHight.fullLevel)		//是否是最远端有目的楼层
            {
                if (floorUpList[level] == 1)
                {
                    floorUpList[level] = 0;

                    elevatorState = STOP;
                    return;
                }
            }
        }

        Sleep(HZ);
    } while (true);
}

void Elevator::liftUp()
{
    int level;
    do {
        elevatorHight.nowHight += elevatorHight.moveSpeed;
        level = elevatorHight.nowHight / elevatorHight.levelHigh;

        int i;
        for ( i = level + 1; i < elevatorHight.fullLevel; i++)			//检测目的楼层
        {
            if ((floorUpList[i] == 1) || (panelButtonList[i] == 1))
            {
                break;
            }
        }

        if (elevatorHight.nowHight % elevatorHight.levelHigh == 0)		//有信号，则停止
        {
            if ((floorUpList[level] == 1) || (panelButtonList[level] == 1))
            {
                floorUpList[level] = 0;
                panelButtonList[level] = 0;

                elevatorState = STOP;
                return;
            }
            if (i == elevatorHight.fullLevel)		//是否是最远端有目的楼层
            {
                if (floorDownList[level] == 1)
                {
                    floorDownList[level] = 0;

                    elevatorState = STOP;
                    return;
                }
            }
        }

        Sleep(HZ);
    } while (true);
}

void Elevator::liftStop()
{
    while (true)
    {
        int level = elevatorHight.nowHight / elevatorHight.levelHigh;
        //当电梯门未关闭
        if (doorState != CLOSE)
        {
            Sleep(HZ*10);
            continue;
        }
        //当电梯门关闭时
        if (liftDirection == LIFT)
        {
            //确认上行信号，无信号则改为SUSPEND

            for (int i = level + 1; i < elevatorHight.fullLevel; i++)
            {
                if (floorUpList[i] || panelButtonList[i])
                {
                    liftDirection = LIFT;
                    elevatorState = UP;
                    return;
                }
            }
            for (int i = elevatorHight.fullLevel; i > level ; i--)	//最远端还有未完成的下行请求
            {
                if (floorDownList[i])
                {
                    liftDirection = LIFT;
                    elevatorState = UP;
                    return;
                }
            }
            floorDownList[level] = 0;
            liftDirection = SUSPEND;
        }
        else if (liftDirection == DROP)
        {
            //确认下行信号，无信号则改为SUSPEND
            for (int i = 0; i < level; i++)
            {
                if (floorDownList[i] || panelButtonList[i])
                {
                    liftDirection = DROP;
                    elevatorState = DOWN;
                    return;
                }
            }
            for (int i = 0; i < level; i++)	//最远端还有未完成的上行请求
            {
                if (floorUpList[i])
                {
                    liftDirection = DROP;
                    elevatorState = DOWN;
                    return;
                }
            }
            liftDirection = SUSPEND;
        }
        else
        {//当电梯悬停时
            //检测悬停楼层信号
            if (floorDownList[level] || floorUpList[level] || panelButtonList[level])
            {
                doorState = OPENING;
                floorDownList[level] = 0;
                floorUpList[level] = 0;
                panelButtonList[level] = 0;
                continue;
            }
            //检测悬停位置楼层上部分信号
            for (int i = level + 1; i < elevatorHight.fullLevel; i++)
            {
                if (floorDownList[i] || floorUpList[i] || panelButtonList[i])
                {
                    liftDirection = LIFT;
                }
            }
            //检测悬停楼层下部分信号
            for (int i = level - 1; i >= 0; i--)
            {
                if (floorDownList[i] || floorUpList[i] || panelButtonList[i])
                {
                    liftDirection = DROP;
                }
            }
        }
        Sleep(1);
    }
}

//电梯线程
DWORD WINAPI Elevator::elevatorThread(void* p)
{
    Elevator *elevator = (Elevator*)p;

    while (true)
    {
        switch (elevator->elevatorState)
        {
        case UP:
            elevator->liftUp();
            break;
        case DOWN:
            elevator->liftDown();
            break;
        case STOP:
            elevator->liftStop();
            break;
        }
        Sleep(1);
    }

    return 0;
}
