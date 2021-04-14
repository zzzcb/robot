//
// Created by zcb on 4/14/21.
//

/*
 * 主要解决一个server多个client的问题：
 *  1，server 可以中止指定的client ，而不是前面的一下中止所有的client
 *  2，client取消操作的时候，避免取消所有的client
 */

#include <ros/ros.h>
#include <iostream>

#include <QApplication>
#include "ActionServerWindow02.h"

using namespace std;

int main(int argc, char **argv) {
    //1 ros
    string nodeName = "action_server_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //2 qt
    QApplication app(argc, argv);
    ActionServerWindow02 *window = new ActionServerWindow02(&node);
    window->show();

    return app.exec();
}
