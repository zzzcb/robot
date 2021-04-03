//
// Created by zcb on 2021/4/3.
//

#include <iostream>
// ros
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

// qt
#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

using namespace std;

ros::Publisher publisher;
QLineEdit *editLinear, *editAngular;

void slotFuc() {
    geometry_msgs::Twist msg;

    double linearX = editLinear->text().toDouble();
    double angularZ = editAngular->text().toDouble();

    msg.linear.x = linearX;
    msg.angular.z = angularZ * M_PI / 180;

    publisher.publish(msg);
}

int main(int argc, char **argv) {

    //1 node
    string nodeName = "ctrl_turtle_cpp_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string topicName = "/turtle1/cmd_vel";
    publisher = node.advertise<geometry_msgs::Twist>(topicName, 1000);

    //2 qt
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("小乌龟控制器");

    // layout
    QFormLayout formLayout(&window);

    editLinear = new QLineEdit("0.0");
    editAngular = new QLineEdit("0.0");
    formLayout.addRow("线速度", editLinear);
    formLayout.addRow("角速度", editAngular);

    QPushButton sendBtn("发送");
    formLayout.addRow(&sendBtn);

    // event:sendBtn
    QPushButton::connect(&sendBtn, &QPushButton::clicked, &slotFuc);

    window.show();

    return app.exec();
}

