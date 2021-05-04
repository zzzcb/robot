//
// Created by zcb on 4/14/21.
//
#include <iostream>
#include <ros/ros.h>

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "args_use_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    cout << "============" << endl;
    for (int i = 0; i < argc; ++i) {
        cout <<argv[i] << endl;
    }
    cout << "============" << endl;


    ros::spin();
}

