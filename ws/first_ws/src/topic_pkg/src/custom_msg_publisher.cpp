//
// Created by zcb on 2021/4/2.
//

#include <iostream>
#include <ros/ros.h>
#include <demo_msgs/Student.h>

using namespace std;

int main(int argc,char** argv){
    string nodeName = "publisher_custom_msg_cpp_node";
    ros::init(argc,argv,nodeName);
    ros::NodeHandle node;

    string topicName = "/custom/msg/topic";
    ros::Publisher pub = node.advertise<demo_msgs::Student>(topicName,1000);

    ros::Rate rate(1);
    demo_msgs::Student stu;
    int idx = 0;
    while(ros::ok()){
        stu.name = "tom"+to_string(idx++);
        stu.age = idx;
        pub.publish(stu);
        rate.sleep();
    }

    ros::spin();

    return 0;
}










