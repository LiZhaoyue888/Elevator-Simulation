#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"elevator.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_leftDoor_clicked();

    void on_rightDoor_clicked();

    void on_pushButton_clicked();

    void on_startBtn_clicked();

    void on_elevatorButton_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_btn_l1_clicked();

    void on_btn_l2_clicked();

    void on_btn_l3_clicked();

    void on_btn_l4_clicked();

    void on_btn_l5_clicked();

    void on_btn_l6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

private:
    Ui::MainWindow *ui;
    Elevator * ele;
};
#endif // MAINWINDOW_H
