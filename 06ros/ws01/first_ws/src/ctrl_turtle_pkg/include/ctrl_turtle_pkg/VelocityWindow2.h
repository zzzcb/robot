//
// Created by zcb on 2021/4/9.
//

#ifndef CTRL_TURTLE_PKG_VELOCITYWINDOW2_H
#define CTRL_TURTLE_PKG_VELOCITYWINDOW2_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

#include <ros/ros.h>
#include <turtlesim/Pose.h>

class VelocityWindow2 : public QWidget {
public:
    VelocityWindow2(ros::NodeHandle *node, QWidget *parent = nullptr);

    ~VelocityWindow2();

private:
    QLineEdit *editLinear, *editAngular;
    QLabel *labelPosX, *labelPosY, *labelLinearX, *labelAngularZ, *labelTheta;
    QFormLayout *formlayout;
    QPushButton *sendBtn;

    ros::Publisher publisher;
    ros::Subscriber subscriber;
    QTimer *timer;

private:
    void sendMsgEvt(); // slot func
    void displayPose(const turtlesim::Pose::ConstPtr &msg);
    void onUpdate();
};


#endif //CTRL_TURTLE_PKG_VELOCITYWINDOW2_H
