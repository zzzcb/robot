//
// Created by zcb on 2021/4/11.
//

#include <ros/ros.h>
#include <iostream>

#include <QApplication>
#include "FinalPosWindow.h"

using namespace std;

int main(int argc, char **argv) {
    //1 ros
    string nodeName = "cpp_ctrl_turtle_node"; // cpp_ctrl_turtle_node
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //2 qt
    QApplication app(argc, argv);
    FinalPosWindow *window = new FinalPosWindow(&node);
    window->show();

    return app.exec();
}