//
// Created by zcb on 2021/4/3.
//

#include "VelocityWindow.h"
#include <geometry_msgs/Twist.h>


VelocityWindow::VelocityWindow(ros::NodeHandle* node,QWidget* parent): QWidget(parent){
    this->setWindowTitle("小乌龟控制");

    // layout
    this->formlayout = new QFormLayout(this);

    this->editLinear = new QLineEdit("0.0");
    this->editAngular =new QLineEdit("0.0");
    this->formlayout->addRow("线速度", editLinear);
    this->formlayout->addRow("角速度", editAngular);

    this->sendBtn = new QPushButton("发送");
    this->formlayout->addRow(this->sendBtn);

    // event:sendBtn
    QPushButton::connect(this->sendBtn, &QPushButton::clicked,this, &VelocityWindow::sendMsgEvt);

    std::string topicName = "/turtle1/cmd_vel";
    this->publisher = node->advertise<geometry_msgs::Twist>(topicName, 1000);
}

VelocityWindow::~VelocityWindow() {

}

void VelocityWindow::sendMsgEvt() {
    geometry_msgs::Twist msg;

    double linearX = this->editLinear->text().toDouble();
    double angularZ = this->editAngular->text().toDouble();

    msg.linear.x = linearX;
    msg.angular.z = angularZ * M_PI / 180;

    this->publisher.publish(msg);
}
