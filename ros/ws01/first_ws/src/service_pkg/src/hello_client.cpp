//
// Created by zcb on 2021/4/9.
//
#include <ros/ros.h>
#include <iostream>
#include <roscpp_tutorials/TwoInts.h>

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "cpp_client_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string serviceName = "/cpp/service";
    ros::ServiceClient client = node.serviceClient<roscpp_tutorials::TwoInts>(serviceName);

    client.waitForExistence(); // 如果client先于 server 起来，可以一直等server

    roscpp_tutorials::TwoInts service;
    service.request.a = 10;
    service.request.b = 5;
    client.call(service);

    ROS_INFO_STREAM("result is: " << service.response.sum);


    return 0;
}
