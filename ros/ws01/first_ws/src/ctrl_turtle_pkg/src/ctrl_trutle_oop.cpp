//
// Created by zcb on 2021/4/3.
//
#include <iostream>
// ros
#include <ros/ros.h>
// qt
#include <QApplication>
#include "VelocityWindow.h"

using namespace std;

int main(int argc, char **argv) {
    // ros
    string nodeName = "ctrl_turtle_cpp_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    // qt
    QApplication app(argc, argv);

    VelocityWindow * window = new VelocityWindow(&node);
    window->show();

    return app.exec();
}



