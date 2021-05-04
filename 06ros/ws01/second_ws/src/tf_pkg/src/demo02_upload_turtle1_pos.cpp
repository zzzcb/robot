//
// Created by zcb on 4/15/21.
//

#include <iostream>
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <tf/transform_broadcaster.h>

using namespace std;

void uploadToTF(tf::TransformBroadcaster broadcaster,float x,float y,float theta,string frame_id,string child_frame_id){

    tf::Transform input;
    input.setOrigin(tf::Vector3(x, y, 0));// 1, 设置位置


    tf::Quaternion qua;
    qua.setRPY(0, 0, theta); // rpy 是我们人比较熟悉的，通过它来设置四元数
    input.setRotation(qua); // 2, 设置姿态(采用四元数)

    tf::StampedTransform transform(input,
                                   ros::Time::now(),
                                   frame_id,
                                   child_frame_id
    );

    broadcaster.sendTransform(transform);
}




void topicCallback(const turtlesim::Pose::ConstPtr &msg, tf::TransformBroadcaster broadcaster) {
    // 将实时位置 上传到 tf 中
    //cout << msg->x << endl;
    //cout << msg->y << endl;
    //cout << msg->theta << endl;

    float x = msg->x;
    float y = msg->y;
    float theta = msg->theta;
    uploadToTF(broadcaster,x,y,theta,"world","turtle1");
    uploadToTF(broadcaster,-2,0,theta,"turtle1","turtle1_back");
    uploadToTF(broadcaster,0,2,theta,"turtle1","turtle1_left");
    uploadToTF(broadcaster,2,0,theta,"turtle1","turtle1_forward");
    uploadToTF(broadcaster,0,-2,theta,"turtle1","turtle1_right");

}

int main(int argc, char **argv) {

    string nodeName = "demo01_upload_turtle1_pos_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    tf::TransformBroadcaster broadcaster;

    string topicName = "/turtle1/pose"; // 一定要注意 是pose 不是 pos  艹艹艹
    ros::Subscriber sub = node.subscribe<turtlesim::Pose>(topicName, 1000, bind(topicCallback, _1, broadcaster));

    ros::spin();
}




