//
// Created by zcb on 2021/4/9.
//
#include <iostream>
// ros
#include <ros/ros.h>
// qt
#include <QApplication>
#include "VelocityWindow2.h"

using namespace std;

int main(int argc, char **argv) {
    // ros
    string nodeName = "ctrl_turtle_cpp_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    // 解决ROS 和 QT的阻塞冲突问题
    // 第一种方案：
    // 开启一个异步的轮询器
    //ros::AsyncSpinner spinner(1); // 这时，ros的消息回调 就放到了这个子线程去，就不会和QT冲突了.
    //spinner.start();

    // 第二种方案:
    // QT渲染过程中同时也去接收ROS的订阅回调消息。接管QT的渲染机制。



    // qt
    QApplication app(argc, argv);

    VelocityWindow2 * window = new VelocityWindow2(&node);
    window->show();

    return app.exec();
}

