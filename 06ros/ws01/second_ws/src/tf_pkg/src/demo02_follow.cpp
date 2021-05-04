//
// Created by zcb on 4/15/21.
//
#include <ros/ros.h>
#include <iostream>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

using namespace std;

void poseCallback(const turtlesim::Pose::ConstPtr &msg, tf::TransformBroadcaster broadcaster,string turtleName) {
    // 将实时位置 上传到 tf 中

    float x = msg->x;
    float y = msg->y;
    float theta = msg->theta;

    //cout << x << endl;
    //cout << y << endl;
    //cout << theta << endl;

    tf::Transform input;
    input.setOrigin(tf::Vector3(x, y, 0));// 1, 设置位置


    tf::Quaternion qua;
    qua.setRPY(0, 0, theta); // rpy 是我们人比较熟悉的，通过它来设置四元数
    input.setRotation(qua); // 2, 设置姿态(采用四元数)

    tf::StampedTransform transform(input,
                                   ros::Time::now(),
                                   "world",
                                   turtleName
    );
    broadcaster.sendTransform(transform);
}

int main(int argc, char **argv) {

    string nodeName = "demo01_follow_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string turtleName = argv[1];
    string direct = argv[2];

    // ===================================== 生成turtle2
    // 通过 /spawn service来生出一个新的小乌龟
    string serviceName = "/spawn";
    ros::ServiceClient client = node.serviceClient<turtlesim::Spawn>(serviceName);
    client.waitForExistence(); // wait for server

    turtlesim::Spawn service;
    service.request.x = 1.0;
    service.request.y = 1.0;
    service.request.theta = 0;
    service.request.name = turtleName; // 新的小乌龟的名字，不是nodeName
    // 默认起来的小乌龟名字是 turtle1
    client.call(service);

    // ===================================== 将turtle2 的位置上传至 tf
    tf::TransformBroadcaster broadcaster;
    string poseTopicName = "/"+turtleName+"/pose"; // 一定要注意 是pose 不是 pos  艹艹艹
    // 这里的回调是在主线程中的，可能被下面的 while True或其他的东西卡死,所以开一个子线程
    ros::AsyncSpinner spinner(1);// 开启一个子线程 去处理callback
    spinner.start();

    ros::Subscriber sub = node.subscribe<turtlesim::Pose>(poseTopicName, 1000, bind(poseCallback, _1, broadcaster,turtleName));

    // ===================================== 实时获取 turtle1 相对我（turtle2）的位置,并发布turtle1速度
    ros::Rate rate(10);// hz
    tf::TransformListener listener;
    tf::StampedTransform relativePosAngular; // 传出参数

    double kLinear = 0.6;
    double kAngular = 6;  // 角度一般转的更快

    string velTopicName = "/"+turtleName+"/cmd_vel";
    ros::Publisher publisher = node.advertise<geometry_msgs::Twist>(velTopicName, 1000);

    while (ros::ok()) {
        try {
            // 下面一行代码可能会有异常 ，需要处理
            // turtle1 相对于 turtle2 的位置
            listener.lookupTransform(turtleName, "turtle1_"+direct, ros::Time(0), relativePosAngular);
        } catch (exception e) {
            continue; // 直到没有异常
        }

        // 位置
        tf::Vector3 &pos = relativePosAngular.getOrigin();

        // =====================================
        // 根据上面获取到的相对位置来 控制turtle2
        double distance = sqrt(pow(pos.x(), 2) + pow(pos.y(), 2));
        double theta = atan2(pos.y(), pos.x());

        // kLinear 和 kAngular 是系数
        geometry_msgs::Twist twist;
        twist.linear.x = kLinear * distance; // 一开始是最快的，后面逐渐变慢 ~ // 我们之前pid 做的是最终收敛到匀速
        twist.angular.z = kAngular * theta;
        publisher.publish(twist);

        rate.sleep();
    }


    ros::waitForShutdown(); // 配合 spinner

    return 0;
}
