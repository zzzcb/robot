//
// Created by zcb on 7/10/21.
//

/*
 * 获取当前的arm ee_link 的位姿,并保存到文件中
 */

#include <ros/ros.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <Eigen/Eigen>

using namespace std;
int cnt = 13;

/**
 * 四元数转旋转矩阵
 */
Eigen::Matrix3d quaternion2RotationMatrix(const double x, const double y, const double z, const double w) {
    Eigen::Quaterniond q;
    q.x() = x;
    q.y() = y;
    q.z() = z;
    q.w() = w;

    Eigen::Matrix3d R = q.normalized().toRotationMatrix();
    cout << "Quaternion2RotationMatrix result is:" << endl;
    cout << "R = " << endl << R << endl << endl;
    return R;
}


void saveToFile(cv::String filename, cv::String k, cv::Mat &btg) {

    cv::FileStorage fs(filename, cv::FileStorage::APPEND);
    fs << k << btg; // base T gripper ,base 的视角看 gripper
    fs.release();

}


int main(int argc, char **argv) {

    int cnt = 0;

    string nodeName = "cur_pose";
    ros::init(argc, argv, nodeName, ros::init_options::AnonymousName);
    ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    // 获取此时 机械臂 ee_link  的位姿
    moveit::planning_interface::MoveGroupInterface armGroup("arm_group");
    while (ros::ok()) {

        cout << "Enter键保存当前位姿到文件中(输入q退出)" << endl;
        if (getchar() == 'q')
            break;
        auto position = armGroup.getCurrentPose().pose.position;
        auto orientation = armGroup.getCurrentPose().pose.orientation;

        cv::Mat btg = cv::Mat::zeros(4, 4, CV_32F);
        btg.at<float>(0, 3) = position.x;
        btg.at<float>(1, 3) = position.y;
        btg.at<float>(2, 3) = position.z;
        btg.at<float>(3, 3) = 1;

        Eigen::Matrix3d R = quaternion2RotationMatrix(orientation.x, orientation.y, orientation.z,
                                                      orientation.w);
        btg.at<float>(0, 0) = R(0, 0);
        btg.at<float>(0, 1) = R(0, 1);
        btg.at<float>(0, 2) = R(0, 2);

        btg.at<float>(1, 0) = R(1, 0);
        btg.at<float>(1, 1) = R(1, 1);
        btg.at<float>(1, 2) = R(1, 2);

        btg.at<float>(2, 0) = R(2, 0);
        btg.at<float>(2, 1) = R(2, 1);
        btg.at<float>(2, 2) = R(2, 2);

        saveToFile("ee_link_pose.xml", "pic" + to_string(cnt++), btg);
    }

    return 0;
}




