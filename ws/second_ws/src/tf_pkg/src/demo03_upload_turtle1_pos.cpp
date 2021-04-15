//
// Created by zcb on 4/15/21.
//

#include <iostream>
#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <tf/transform_broadcaster.h>

using namespace std;


void uploadToTF(tf::TransformBroadcaster broadcaster, float x, float y, float theta, string frame_id,
                string child_frame_id) {

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


int alpha = 0; // 绕着 画圆 0 - 360
void topicCallback(const turtlesim::Pose::ConstPtr &msg, tf::TransformBroadcaster broadcaster) {
    // 将实时位置 上传到 tf 中
    //cout << msg->x << endl;
    //cout << msg->y << endl;
    //cout << msg->theta << endl;

    float x = msg->x;
    float y = msg->y;
    float theta = msg->theta;

    uploadToTF(broadcaster, x, y, theta, "world", "turtle1");

    double r = 5;
    double alpha_rad = alpha * M_PI / 180;
    // 画圆
    //uploadToTF(broadcaster, r * cos(alpha_rad), r * sin(alpha_rad), theta, "turtle1", "point");

    // 画心形
    // x = 16 (sin t)^3
    // y = 13 cos t - 5cos(2t) -cos(4t)
    double pointX = r * 16.0 / 37.0 * pow(sin(alpha_rad), 3);
    double pointY = r * 13.0 / 37.0 * cos(alpha_rad) - r * 5.0 / 37 * cos(2 * alpha_rad) - cos(4 * alpha_rad);
    uploadToTF(broadcaster, pointX, pointY, theta, "turtle1", "point");
    alpha++;

    if (alpha == 360)
        alpha = 0;
}

int main(int argc, char **argv) {

    string nodeName = "demo01_upload_turtle1_pos_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    tf::TransformBroadcaster broadcaster;

    string topicName = "/turtle1/pose"; // 一定要注意 是pose 不是 pos  艹艹艹
    ros::Subscriber sub = node.subscribe<turtlesim::Pose>(topicName, 1000, bind(topicCallback, _1, broadcaster));

    ros::spin();
    // 调整 回调函数处理的频率

}




