//
// Created by zcb on 2021/4/2.
//

#include <iostream>
#include <ros/ros.h>
#include <demo_msgs/Student.h>

using namespace std;

void topicCallBk(const demo_msgs::Student::ConstPtr & msg){
    cout << "---" << endl;
    cout << "name:"<< msg->name << endl;
    cout << "age:"<< msg->age << endl;
}


int main(int argc,char** argv){
    string nodeName = "subscriber_customer_msg_cpp_node";
    ros::init(argc,argv,nodeName);
    ros::NodeHandle node;


    string topicName = "/custom/msg/topic";
    ros::Subscriber sub = node.subscribe(topicName,1000,topicCallBk);

    ros::spin();

    return 0;
}












