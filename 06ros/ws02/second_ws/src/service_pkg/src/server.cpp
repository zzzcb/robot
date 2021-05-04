//
// Created by zcb on 5/4/21.
//

#include <ros/ros.h>
#include <iostream>
#include <roscpp_tutorials/TwoInts.h>

bool callback(roscpp_tutorials::TwoIntsRequest &request, roscpp_tutorials::TwoIntsResponse &response) {
    int a = request.a;
    int b = request.b;


    response.sum = a + b;

    return true;
}


int main(int argc, char **argv) {

    std::string nodeName = "server_node";
    ros::init(argc, argv, nodeName);

    ros::NodeHandle node;

    std::string serviceName = "/zcb01/service";
    ros::ServiceServer server = node.advertiseService(serviceName, callback);

    ros::spin();


    return 0;
}











