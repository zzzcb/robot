//
// Created by zcb on 5/14/21.
//

/*
 *  对 视频 进行 去畸变
 *  1. 读取相机内参 01calibration_chessboard.yml
 *  2. 初始化 两个map
 *  3. 执行去畸变
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;


int main(int argc, char **argv) {
    // 1. 读取相机内参
    cv::FileStorage fs("/home/zcb/camera_calibration/01calibration/01calibration_chessboard.yml",
                       cv::FileStorage::READ);

    cv::Size imgSize;
    cv::Mat cameraMatrix; // 相机内参  fx fy u0 v0
    cv::Mat distCoeffs; // k1 k2 p1 p2 k3
    fs["image_size"] >> imgSize;
    fs["camera_matrix"] >> cameraMatrix;
    fs["dist_coeffs"] >> distCoeffs;
    fs.release();

    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix, imgSize, CV_16SC2, map1, map2);

    // remap 去畸变
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "\nCouldn't open the camera\n";
        return -1;
    }
    // 显示原图和去畸变后的图
    while (true) {
        cv::Mat src, dst;
        capture >> src;

        if (src.empty()) {
            break;
        }

        // 执行映射转换
        remap(src, dst, map1, map2,
              cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

        imshow("original", src);
        imshow("undistorted", dst);

        if ((cv::waitKey(30) & 255) == 27) {
            break;
        }
    }
    cv::destroyAllWindows();

    return 0;
}







