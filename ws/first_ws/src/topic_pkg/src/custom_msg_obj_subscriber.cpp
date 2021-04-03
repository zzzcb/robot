//
// Created by zcb on 2021/4/2.
//

#include <iostream>
#include <ros/ros.h>
#include <demo_msgs/Team.h>

using namespace std;

void topicCallBack(const demo_msgs::Team::ConstPtr& msg){
    cout << "===" << endl;
    cout << "team::name "<<msg->name<<endl;
    cout << "team::leader::name " << msg->leader.name << endl;
    cout << "team::leader::age " << msg->leader.age << endl;
}


int main(int argc,char** argv){
    string nodeName = "subscribe_custom_msg_obj_cpp_node";
    ros::init(argc,argv,nodeName);
    ros::NodeHandle node;

    string topicName = "/custom/msg/obj/topic";
    ros::Subscriber sub = node.subscribe(topicName,1000,topicCallBack);

    ros::spin();

    return 0;
}

