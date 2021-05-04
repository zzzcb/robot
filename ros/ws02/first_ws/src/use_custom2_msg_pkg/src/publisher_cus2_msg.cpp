//
// Created by zcb on 5/3/21.
//

#include <ros/ros.h>
#include <iostream>
#include <custom2_msgs/Team.h>


int main(int argc, char **argv) {

    std::string nodeName = "publisher_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    std::string topicName = "/zcb01/topic";
    ros::Publisher publisher = node.advertise<custom2_msgs::Team>(topicName, 1000);

    custom2_msgs::Team msg;
    custom_msgs::Student leader;

    ros::Rate rate(2);
    int idx = 0;
    while (ros::ok()) {
        msg.name = "NCHU" + std::to_string(idx);
        leader.name = "tom" + std::to_string(idx);
        leader.age = idx;
        msg.leader = leader;

        publisher.publish(msg);

        idx++;
        rate.sleep();
    }

    return 0;
}