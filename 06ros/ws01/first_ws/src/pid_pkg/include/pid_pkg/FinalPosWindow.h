//
// Created by zcb on 2021/4/11.
//

#ifndef PID_PKG_FINALPOSWINDOW_H
#define PID_PKG_FINALPOSWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QTimer>

#include <ros/ros.h>
#include <turtlesim/Pose.h>

class FinalPosWindow : public QWidget {
public:
    FinalPosWindow(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~FinalPosWindow();

private:
    QLineEdit *finalPosX, *finalPosY;
    QFormLayout *formlayout;
    QPushButton *sendBtn;


    ros::Publisher velPublisher;
    ros::Publisher plotVelPublisher;
    ros::Subscriber posSubscriber;

    double curX;
    double curY;
    QTimer *timer;

private:
    void sendMsgEvt(); // slot func
    void poseCallback(const turtlesim::Pose::ConstPtr& msg);
    void moveTurtle();
    double calcDistance(double dstX,double dstY);
    void onUpdate();
};

#endif //PID_PKG_FINALPOSWINDOW_H
