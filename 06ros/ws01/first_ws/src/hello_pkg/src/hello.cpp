//
// Created by zcb on 2021/4/1.
//
#include <ros/ros.h>

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "hellocpp_node";
    // init
    ros::init(argc, argv, nodeName);
    // node object
    ros::NodeHandle node;

    ros::Rate rate(2);// hz 要在while 中使用 rate.sleep()
    int i = 0;
    while (ros::ok()) {  // ros::ok() 如果用户ctrl+c ，就会停止了
        cout << "hellopkg's cpp" << i++ << endl;
        rate.sleep();
    }

    ros::spin();

    return 0;
}







