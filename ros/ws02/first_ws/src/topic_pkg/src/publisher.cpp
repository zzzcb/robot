//
// Created by zcb on 5/3/21.
//

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>


int main(int argc, char **argv) {

    std::string nodeName = "publisher_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string topicName = "/zcb01/topic";
    ros::Publisher publisher = node.advertise<std_msgs::String>(topicName, 1000);
    std_msgs::String msg;


    ros::Rate rate(2); // hz = 2
    int idx = 0;
    while (ros::ok()) {
        msg.data = "hello " + std::to_string(idx);
        publisher.publish(msg);

        idx++;
        rate.sleep();
    }


    return 0;
}
