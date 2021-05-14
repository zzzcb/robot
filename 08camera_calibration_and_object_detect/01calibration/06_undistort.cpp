//
// Created by zcb on 5/14/21.
//

/*
 *  对 单个照片进行 去畸变
 *  1. 读取相机内参 01calibration_chessboard.yml
 *  2. 执行去畸变
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;


int main(int argc, char **argv) {
    // 1. 读取相机内参
    cv::FileStorage fs("/home/zcb/camera_calibration/01calibration/01calibration_chessboard.yml",
                       cv::FileStorage::READ);

    cv::Mat cameraMatrix; // 相机内参  fx fy u0 v0
    cv::Mat distCoeffs; // k1 k2 p1 p2 k3
    fs["camera_matrix"] >> cameraMatrix;
    fs["dist_coeffs"] >> distCoeffs;
    fs.release();

    cv::Mat src = cv::imread("/home/zcb/camera_calibration/01calibration/images/image_01.jpg");

    // 去 畸变
    cv::Mat dst;
    cv::undistort(src,dst,cameraMatrix,distCoeffs);
    cv::imshow("src",src);
    cv::imshow("dst",dst);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
