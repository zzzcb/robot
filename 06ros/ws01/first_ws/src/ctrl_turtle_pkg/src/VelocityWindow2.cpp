//
// Created by zcb on 2021/4/9.
//

#include <geometry_msgs/Twist.h>
#include "VelocityWindow2.h"

VelocityWindow2::VelocityWindow2(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("小乌龟控制");

    // layout
    this->formlayout = new QFormLayout(this);

    this->editLinear = new QLineEdit("0.0");
    this->editAngular = new QLineEdit("0.0");
    this->labelPosX = new QLabel("0.0");
    this->labelPosY = new QLabel("0.0");
    this->labelLinearX = new QLabel("0.0");
    this->labelAngularZ = new QLabel("0.0");
    this->labelTheta = new QLabel("0.0");
    this->sendBtn = new QPushButton("发送");

    this->formlayout->addRow("线速度", editLinear);
    this->formlayout->addRow("角速度", editAngular);
    this->formlayout->addRow("当前X", labelPosX);
    this->formlayout->addRow("当前Y", labelPosY);
    this->formlayout->addRow("当前线速度", labelLinearX);
    this->formlayout->addRow("当前角速度", labelAngularZ);
    this->formlayout->addRow("当前角度", labelTheta);
    this->formlayout->addRow(this->sendBtn);

    // event:sendBtn
    QPushButton::connect(this->sendBtn, &QPushButton::clicked, this, &VelocityWindow2::sendMsgEvt);

    std::string pubTopicName = "/turtle1/cmd_vel";
    this->publisher = node->advertise<geometry_msgs::Twist>(pubTopicName, 1000);

    std::string subTopicName = "/turtle1/pose";
    this->subscriber = node->subscribe(subTopicName, 1000, &VelocityWindow2::displayPose, this);


    // ROS  和 QT 阻塞冲突第二种解决方案:接管QT的渲染机制
    this->timer = new QTimer(this);
    this->timer->setInterval(16); // 16ms
    this->timer->start();
    QTimer::connect(this->timer, &QTimer::timeout, this, &VelocityWindow2::onUpdate);

}

VelocityWindow2::~VelocityWindow2() {


}

void VelocityWindow2::sendMsgEvt() {
    geometry_msgs::Twist msg;

    double linearX = this->editLinear->text().toDouble();
    double angularZ = this->editAngular->text().toDouble();

    msg.linear.x = linearX;
    msg.angular.z = angularZ * M_PI / 180;

    this->publisher.publish(msg);
}

void VelocityWindow2::displayPose(const turtlesim::Pose::ConstPtr &msg) {
    float posX = msg->x;
    float posY = msg->y;
    float linearX = msg->linear_velocity;
    float angularZ = msg->angular_velocity * 180 / M_PI;
    float theta = msg->theta * 180 / M_PI;

    this->labelPosX->setText(QString::fromStdString(std::to_string(posX)));
    this->labelPosY->setText(QString::fromStdString(std::to_string(posY)));
    this->labelLinearX->setText(QString::fromStdString(std::to_string(linearX)));
    this->labelAngularZ->setText(QString::fromStdString(std::to_string(angularZ)));
    this->labelTheta->setText(QString::fromStdString(std::to_string(theta)));
}

void VelocityWindow2::onUpdate() {
    ros::spinOnce(); // ros 回调
    this->update(); // qt 回调

    if (!ros::ok()) { // 如果当前 node 挂了,就是ctrl+c 了
        this->close(); // qt 也要关闭
    }
}
