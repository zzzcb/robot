//
// Created by zcb on 4/14/21.
//

#include <ros/ros.h>
#include <iostream>

#include <QApplication>
#include "ActionServerWindow.h"

using namespace std;

int main(int argc, char **argv) {
    //1 ros
    string nodeName = "action_server_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //2 qt
    QApplication app(argc, argv);
    ActionServerWindow *window = new ActionServerWindow(&node);
    window->show();

    return app.exec();
}
