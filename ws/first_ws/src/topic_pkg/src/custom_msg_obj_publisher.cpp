//
// Created by zcb on 2021/4/2.
//
#include <iostream>
#include <ros/ros.h>
#include <demo_msgs/Team.h>

using namespace std;

int main(int argc, char **argv) {
    string nodeName = "publish_custom_msg_obj_cpp_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string topicName = "/custom/msg/obj/topic";
    ros::Publisher pub = node.advertise<demo_msgs::Team>(topicName, 1000);

    demo_msgs::Team team;
    demo_msgs::Student stu;
    ros::Rate rate(1);
    int idx = 0;
    while (ros::ok()) {
        team.name = "NCHU" + to_string(idx);
        stu.name = "tom " + to_string(idx);
        stu.age = idx;
        team.leader = stu;
        pub.publish(team);

        idx++;
        rate.sleep();
    }
    ros::spin();

    return 0;
}







