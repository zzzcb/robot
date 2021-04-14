//
// Created by zcb on 4/13/21.
//
#include <ros/ros.h>
#include <iostream>

#include <QApplication>
#include "SimpleServerWindow.h"

using namespace std;

int main(int argc, char **argv) {
    //1 ros
    string nodeName = "simple_action_server_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //2 qt
    QApplication app(argc, argv);
    SimpleServerWindow *window = new SimpleServerWindow(&node);
    window->show();

    return app.exec();
}

