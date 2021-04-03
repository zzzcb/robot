//
// Created by zcb on 2021/4/2.
//
#include <iostream>
#include <ros/ros.h>
#include <demo_msgs/Team4.h>

using namespace std;

int main(int argc, char **argv) {
    string nodeName = "publish_custom_msg_arr_cpp_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string topicName = "/custom/msg/arr/topic";
    ros::Publisher pub = node.advertise<demo_msgs::Team4>(topicName, 1000);

    demo_msgs::Team4 team;
    demo_msgs::Student leader;
    std_msgs::String intro;
    geometry_msgs::Twist location;
    demo_msgs::Student member1;
    demo_msgs::Student member2;

    ros::Rate rate(1);
    int idx = 0;
    while (ros::ok()) {
        team.name = "NCHU" + to_string(idx);
        leader.name = "leader " + to_string(idx);
        leader.age = idx;
        team.leader = leader;
        intro.data = "our team is niubi!";
        team.intro = intro;

        member1.name = "mem01";
        member1.age = 18;
        member2.name = "mem02";
        member2.age = 28;
        team.members = {member1, member2};

        pub.publish(team);

        idx++;
        rate.sleep();
    }
    ros::spin();

    return 0;
}
