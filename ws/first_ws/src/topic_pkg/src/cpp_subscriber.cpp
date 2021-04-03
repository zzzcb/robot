//
// Created by zcb on 2021/4/2.
//
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>

using namespace std;

void topicCallback(const std_msgs::String::ConstPtr & msg){
    cout << msg->data <<endl;
}

int main(int argc,char** argv){

    string nodeName = "cpp_subscriber_node";
    ros::init(argc,argv,nodeName);
    ros::NodeHandle node;

    // node.subscribe() 返回的对象一定要接受，不然就会被c++ 回收了
    ros::Subscriber sub = node.subscribe("/cpp/topic",1000,topicCallback);

    ros::spin();
}








