//
// Created by zcb on 5/3/21.
//

#include <iostream>
#include <ros/ros.h>
#include <custom_msgs/Student.h>


void topicCallback(const custom_msgs::Student::ConstPtr &msg) {
    std::cout << msg->name << " || " << msg->age << std::endl;
}

int main(int argc, char **argv) {

    std::string nodeName = "subscriber_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    std::string topicName = "/zcb01/topic";
    ros::Subscriber sub = node.subscribe(topicName, 1000, topicCallback);

    ros::spin();
}

