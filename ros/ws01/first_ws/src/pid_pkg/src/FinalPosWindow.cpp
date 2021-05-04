//
// Created by zcb on 2021/4/11.
//

#include "FinalPosWindow.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <thread>

FinalPosWindow::FinalPosWindow(ros::NodeHandle *node, QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("小乌龟控制");

    this->timer = new QTimer(this);
    this->timer->setInterval(16); // 16ms
    this->timer->start();
    QTimer::connect(this->timer, &QTimer::timeout, this, &FinalPosWindow::onUpdate);

    // ui
    this->formlayout = new QFormLayout(this);

    this->finalPosX = new QLineEdit("10.54");
    this->finalPosY = new QLineEdit("5.54");
    this->sendBtn = new QPushButton("执行");

    this->formlayout->addRow("目标位置X", finalPosX);
    this->formlayout->addRow("目标位置Y", finalPosY);
    this->formlayout->addRow(this->sendBtn);

    // event:sendBtn
    QPushButton::connect(this->sendBtn, &QPushButton::clicked, this, &FinalPosWindow::sendMsgEvt);

    // publisher
    std::string velTopicName = "/turtle1/cmd_vel";
    this->velPublisher = node->advertise<geometry_msgs::Twist>(velTopicName, 1000);

    std::string plotVelTopicName = "/plot/vel";
    this->plotVelPublisher = node->advertise<std_msgs::Float64>(plotVelTopicName, 1000);

    // subscriber
    std::string posTopicName = "/turtle1/pose";
    this->posSubscriber = node->subscribe(posTopicName, 1000, &FinalPosWindow::poseCallback, this);


}

FinalPosWindow::~FinalPosWindow() {


}

// 小乌龟 到达 目标点
void FinalPosWindow::sendMsgEvt() {

    // 开启子线程 去执行 这个任务  这样就可以不卡死主线程了
    new std::thread(&FinalPosWindow::moveTurtle, this);

}

/*
void FinalPosWindow::moveTurtle() {
    // 小乌龟模拟器，默认 如果最后一次消息会 再走1s
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    double time = 5; // 耗时
    double hz = 10;
    ros::Rate rate(hz);

    double distance = this->calcDistance(dstX, dstY);
    double linearX = distance / time; // 线速度
    for (int i = 0; i < time * hz; i++) { // 该for 循环 总共耗时 time

        f64.data = linearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = linearX;
        twist.angular.z = 0;
        this->velPublisher.publish(twist);

        rate.sleep();
    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);

}
*/
void FinalPosWindow::moveTurtle() {
    geometry_msgs::Twist twist;
    std_msgs::Float64 f64;

    // dest pose
    double dstX = this->finalPosX->text().toDouble();
    double dstY = this->finalPosY->text().toDouble();

    double time = 5; // 耗时
    double hz = 10;
    ros::Rate rate(hz);

    double distance = this->calcDistance(dstX, dstY);
    double linearX = 0; // 初始速度应为0

    // 应该实时计算距离，接近终点的时候 跳出循环
    while (distance > 0.01) { // 该while 循环 总共耗时 time

        f64.data = linearX;
        this->plotVelPublisher.publish(f64);

        twist.linear.x = linearX;
        twist.angular.z = 0;
        this->velPublisher.publish(twist);

        rate.sleep();

        distance = this->calcDistance(dstX, dstY);
        time -= 1 / hz; // 剩余的时间   1/hz 是一个循环所需的时间
        linearX = distance / time;
    }

    // 最后1s 也不让 它走了
    twist.linear.x = 0;
    twist.angular.z = 0;
    this->velPublisher.publish(twist);

}

void FinalPosWindow::poseCallback(const turtlesim::Pose::ConstPtr &msg) {
    this->curX = msg->x;
    this->curY = msg->y;
}

double FinalPosWindow::calcDistance(double dstX, double dstY) {
    double deltaX = dstX - this->curX;
    double deltaY = dstY - this->curY;

    return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}


void FinalPosWindow::onUpdate() {
    ros::spinOnce(); // ros 回调
    this->update(); // qt 回调

    if (!ros::ok()) { // 如果当前 node 挂了,就是ctrl+c 了
        this->close(); // qt 也要关闭
    }
}



