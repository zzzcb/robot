//
// Created by zcb on 21-9-10.
//

#include "hello_pkg/fuck2.h"

#include <std_msgs/String.h>
#include <pluginlib/class_list_macros.h>


namespace hello_pkg_ns2 {
    void Fuck2::onInit() {
        nh_ = ros::NodeHandle();
        pub_ = nh_.advertise<std_msgs::String>("topic2", 10);
        timer_ = nh_.createTimer(ros::Duration(1.0), boost::bind(&Fuck2::timerCb, this));
        cnt_ = 100;
    }

    void Fuck2::timerCb() {
        std_msgs::String msg;
        msg.data = "zzzcb2 " + std::to_string(cnt_++);
        pub_.publish(msg);
    }
}

PLUGINLIB_EXPORT_CLASS(hello_pkg_ns2::Fuck2, nodelet::Nodelet)
