//
// Created by zcb on 2021/4/10.
//
#include <ros/ros.h>
#include <iostream>

#include <QApplication>
#include "MainWindow.h"

using namespace std;

int main(int argc, char **argv) {
    //1 ros
    string nodeName = "cpp_ctrl_turtle_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //2 qt
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow(&node);
    window->show();

    return app.exec();
}











