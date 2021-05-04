//
// Created by zcb on 5/3/21.
//

#include <ros/ros.h>
#include <iostream>
#include <custom_msgs/Student.h>


int main(int argc, char **argv) {

    std::string nodeName = "publisher_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    std::string topicName = "/zcb01/topic";
    ros::Publisher publisher = node.advertise<custom_msgs::Student>(topicName, 1000);

    custom_msgs::Student msg;

    ros::Rate rate(2);
    int idx = 0;
    while (ros::ok()) {
        msg.name = "tom" + std::to_string(idx);
        msg.age = idx;

        publisher.publish(msg);

        idx++;
        rate.sleep();
    }

    return 0;
}
