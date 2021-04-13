//
// Created by zcb on 2021/4/11.
//

#ifndef PID_PKG_FINALPOSWINDOW2_H
#define PID_PKG_FINALPOSWINDOW2_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QTimer>

#include <ros/ros.h>
#include <turtlesim/Pose.h>

class FinalPosWindow2 : public QWidget {
public:
    FinalPosWindow2(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~FinalPosWindow2();

private:
    QLineEdit *finalPosX, *finalPosY,*kpEditLine,*kiEditLine,*kdEditLine;
    QFormLayout *formlayout;
    QPushButton *sendBtn;

    QPushButton *sweepVBtn; // 纵向扫地
    QPushButton *sweepHBtn; // 纵向扫地
    QPushButton *sweepHuiBtn; //回子形扫地


    ros::Publisher velPublisher;
    ros::Publisher plotVelPublisher;
    ros::Subscriber posSubscriber;

    double curX;
    double curY;
    double curTheta;
    QTimer *timer;

private:
    void sendMsgEvt();
    void poseCallback(const turtlesim::Pose::ConstPtr& msg);
    void moveTurtle();
    double calcDistance(double dstX,double dstY);
    double calcThetaDisplacement(double dstX,double dstY); //
    void onUpdate();
    void clickSweepV();
    void sweepV();
    void moveToPoint(double dstX,double dstY);

};

#endif //PID_PKG_FINALPOSWINDOW2_H
