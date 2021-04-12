#include "mainwindow.h"
#include<windows.h>
#include"elevator.h"

extern Elevator* globalElevator;

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //

    //
    return a.exec();
}
