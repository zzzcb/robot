//
// Created by zcb on 2021/4/10.
//

#ifndef CTRL_TURTLE2_PKG_MAINWINDOW_H
#define CTRL_TURTLE2_PKG_MAINWINDOW_H

#include <ros/ros.h>
#include <QWidget>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QTimer>

class MainWindow : public QWidget {
public:
    MainWindow(ros::NodeHandle* node,QWidget *parent = nullptr);

    ~MainWindow();

private:
    // ui
    QFormLayout* ly;

    QPushButton* clearBtn;

    QPushButton* resetBtn;

    QLineEdit *spawnX,*spawnY,*spawnTheta,*spawnName;
    QPushButton* spawnBtn;

    QLineEdit *killName ;
    QPushButton* killBtn;

    QLineEdit *setPenName,*setPenR,*setPenG,*setPenB ,*setPenWidth;
    QCheckBox *setPenOff;
    QPushButton* setPenBtn;

    QLineEdit *abs_name,*abs_x,*abs_y ,*abs_theta;
    QPushButton* teleportAbsoluteBtn;

    QLineEdit *rel_name,*rel_linear,*rel_angular;
    QPushButton* teleportRelativeBtn;

    void setUI();

private: // 事件
    void clickClear();
    void clickReset();
    void clickSpawn();
    void clickKill();
    void clickSetPen();
    void clickAbs();
    void clickRel();


    void connectSlot();

private:
    // update
    void onUpdate();
    QTimer* updateTimer;

    ros::NodeHandle * node;

};


#endif //CTRL_TURTLE2_PKG_MAINWINDOW_H
