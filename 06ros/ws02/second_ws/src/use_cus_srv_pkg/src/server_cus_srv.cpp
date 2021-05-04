//
// Created by zcb on 5/4/21.
//

#include <ros/ros.h>
#include <iostream>
#include <custom_srvs/NumOption.h>

bool callback(custom_srvs::NumOptionRequest &request, custom_srvs::NumOptionResponse &response) {
    double a = request.a;
    double b = request.b;
    std::string op = request.op;
    if (op == "+") {
        response.res = a + b;
    } else if (op == "-") {
        response.res = a - b;
    } else if (op == "*") {
        response.res = a * b;
    } else if (op == "/") {
        response.res = a / b;
    } else if (op == "%") {
        response.res = fmod(a, b);
    } else {
        return false;
    }
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

