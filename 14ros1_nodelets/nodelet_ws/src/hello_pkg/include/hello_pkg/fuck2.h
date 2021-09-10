//
// Created by zcb on 21-9-10.
//

#ifndef HELLO_PKG_FUCK2_H
#define HELLO_PKG_FUCK2_H

#include <ros/ros.h>
#include <nodelet/nodelet.h>

namespace hello_pkg_ns2 {

    class Fuck2 : public nodelet::Nodelet {
    public:
        void onInit();
        void timerCb();
    private:
        ros::NodeHandle nh_;
        ros::Timer timer_;
        ros::Publisher pub_;
        int cnt_;
    };
}

#endif //HELLO_PKG_FUCK2_H
