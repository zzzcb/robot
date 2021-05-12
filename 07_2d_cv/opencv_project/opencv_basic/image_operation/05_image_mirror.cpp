//
// Created by zcb on 5/7/21.
//
/*
 * 图片 镜面 反转
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");
    cv::imshow("lena", src);

    // 新的 图片 width,2*height   src
    cv::Mat res = cv::Mat::zeros(2 * src.rows, src.cols, CV_8UC3);

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            res.at<cv::Vec3b>(i, j) = src.at<cv::Vec3b>(i, j);
            res.at<cv::Vec3b>(res.rows - i - 1, j) = src.at<cv::Vec3b>(i, j);
        }
    }
    cv::imshow("res", res);

    // 使用 系统提供的 函数 来进行反转
    cv::Mat dst;
    cv::flip(src,dst,0); // 0 :绕 x ,正数:绕 y ,负数:绕xy
    cv::imshow("绕x",dst);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
