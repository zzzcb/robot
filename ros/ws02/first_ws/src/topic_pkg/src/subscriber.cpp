//
// Created by zcb on 5/3/21.
//

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>

void callback(const std_msgs::String::ConstPtr &msg) {
    std::cout << msg->data << std::endl;

}


int main(int argc, char **argv) {
    std::string nodeName = "subscriber_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string topicName = "/zcb01/topic";
    ros::Subscriber subscriber = node.subscribe(topicName, 1000,callback);

    ros::spin();


    return 0;
}
