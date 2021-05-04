//
// Created by zcb on 5/3/21.
//
#include <iostream>
#include <ros/ros.h>


int main(int argc, char **argv) {

    std::string nodeName = "hello_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;


    ros::Rate rate(2);

    while (ros::ok()) {
        std::cout << "hello ros" << std::endl;


        rate.sleep();
    }
    ros::spin();


    return 0;
}