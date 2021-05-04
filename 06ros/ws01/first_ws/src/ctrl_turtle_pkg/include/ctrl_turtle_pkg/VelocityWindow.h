//
// Created by zcb on 2021/4/3.
//

#ifndef CTRL_TURTLE_PKG_VELOCITYWINDOW_H
#define CTRL_TURTLE_PKG_VELOCITYWINDOW_H

#include <iostream>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>

#include <ros/ros.h>

class VelocityWindow : public QWidget {
public:
    VelocityWindow(ros::NodeHandle* node, QWidget *parent = nullptr);

    ~VelocityWindow();

private:
    QLineEdit *editLinear, *editAngular;
    QFormLayout *formlayout;
    QPushButton *sendBtn;

    ros::Publisher publisher;

private:
    void sendMsgEvt(); // slot func

};


#endif //CTRL_TURTLE_PKG_VELOCITYWINDOW_H
