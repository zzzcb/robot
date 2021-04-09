//
// Created by zcb on 2021/4/9.
//


#include <ros/ros.h>
#include <iostream>
#include <demo_srvs/NumOption.h>

using namespace std;

bool client_callback(demo_srvs::NumOptionRequest &request, demo_srvs::NumOptionResponse &response) {
    string option = request.option;
    if (option == "+") {
        response.result = request.a + request.b;
    } else if (option == "-") {
        response.result = request.a - request.b;
    } else if (option == "*") {
        response.result = request.a * request.b;
    } else if (option == "/") {
        response.result = request.a / request.b;
    } else if (option == "%") {
        response.result = fmod(request.a, request.b);
    } else {
        return false;
    }
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








