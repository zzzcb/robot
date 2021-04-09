//
// Created by zcb on 2021/4/9.
//

#include <ros/ros.h>
#include <iostream>
#include <roscpp_tutorials/TwoInts.h>

using namespace std;

bool client_callback(roscpp_tutorials::TwoIntsRequest &request, roscpp_tutorials::TwoIntsResponse &response) {

    response.sum = request.a + request.b;

    return true;
}


int main(int argc, char **argv) {

    string nodeName = "cpp_server_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    string serviceName = "/cpp/service";
    const ros::ServiceServer &server = node.advertiseService(serviceName, client_callback);

    ros::spin();

    return 0;
}




