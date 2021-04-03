//
// Created by zcb on 2021/4/2.
//

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h> // 引入 ros中的标准消息

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "cpp_publisher_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string topicName = "/cpp/topic";
    ros::Publisher publisher = node.advertise<std_msgs::String>(topicName, 1000);

    std_msgs::String msg;
    ros::Rate rate(1);
    int idx = 0;
    while (ros::ok()) {
        msg.data = "hello" + to_string(idx++);
        publisher.publish(msg);
        rate.sleep();
    }

    ros::spin();

    return 0;
}

