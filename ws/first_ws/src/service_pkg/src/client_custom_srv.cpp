//
// Created by zcb on 2021/4/9.
//

#include <ros/ros.h>
#include <iostream>
#include <demo_srvs/NumOption.h>

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "cpp_client_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string serviceName = "/cpp/service";
    ros::ServiceClient client = node.serviceClient<demo_srvs::NumOption>(serviceName);

    client.waitForExistence(); // 如果client先于 server 起来，可以一直等server

    demo_srvs::NumOption service;
    service.request.a = 10;
    service.request.b = 5;
    service.request.option = "*";
    bool flag = client.call(service);
    if (flag) {
        ROS_INFO_STREAM("result is: " << service.response.result);
    } else {
        ROS_DEBUG_STREAM("call fail");
    }


    return 0;
}


