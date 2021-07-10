//
// Created by zcb on 7/8/21.
//
/*
 * 根据02计算得到的相机内参和畸变系数对单个图片进行去畸变
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;


int main(int argc, char **argv) {
    // 1. 读取相机内参
    cv::FileStorage fs("/home/zcb/gazebo_camera_calibration/src/common_pkg/calibration_result/camera_in.xml",
                       cv::FileStorage::READ);

    cv::Mat cameraInMatrix; // 相机内参  fx fy u0 v0
    cv::Mat distCoeffs; // k1 k2 p1 p2 k3
    fs["camera_in_matrix"] >> cameraInMatrix;
    fs["dist_coeffs"] >> distCoeffs;
    fs.release();

    cv::Mat src = cv::imread("/home/zcb/gazebo_camera_calibration/src/common_pkg/images/pic65.png");

    // 去 畸变
    cv::Mat dst;
    cv::undistort(src,dst,cameraInMatrix,distCoeffs);
    cv::imshow("src",src);
    cv::imshow("dst",dst);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

