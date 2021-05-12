//
// Created by zcb on 5/8/21.
//
/*
 * 彩色图 反转
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg");

    cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC3);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {

            cv::Vec3b color = src.at<cv::Vec3b>(i, j);
            uint8_t B = 255 - color[0];
            uint8_t G = 255 - color[1];
            uint8_t R = 255 - color[2];

             dst.at<cv::Vec3b>(i, j) = cv::Vec3b(B, G, R);
        }
    }
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}

