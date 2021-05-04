//
// Created by zcb on 5/3/21.
//

#include <ros/ros.h>
#include <iostream>
#include <custom4_msgs/Team.h>


int main(int argc, char **argv) {

    std::string nodeName = "publisher_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    std::string topicName = "/zcb01/topic";
    ros::Publisher publisher = node.advertise<custom4_msgs::Team>(topicName, 1000);

    custom4_msgs::Team msg;
    custom_msgs::Student leader;

    custom_msgs::Student mem1;
    custom_msgs::Student mem2;
    custom_msgs::Student mem3;

    ros::Rate rate(0.5);
    int idx = 0;
    while (ros::ok()) {
        msg.name = "NCHU" + std::to_string(idx);
        leader.name = "tom" + std::to_string(idx);
        leader.age = idx;
        msg.leader = leader;
        msg.intro.data = "niu bi 战队";

        msg.members.clear();
        mem1.name = "成员01";mem1.age = idx;msg.members.push_back(mem1);
        mem2.name = "成员02";mem2.age = idx+1;msg.members.push_back(mem2);
        mem3.name = "成员03";mem3.age = idx+2;msg.members.push_back(mem3);

        publisher.publish(msg);

        idx++;
        rate.sleep();
    }

    return 0;
}