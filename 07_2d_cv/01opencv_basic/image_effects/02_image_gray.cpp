//
// Created by zcb on 5/8/21.
//

/*
 * 图片的灰度处理
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");

    // 灰度图原理
    cv::Mat gray = cv::Mat::zeros(src.size(), CV_8UC1);// uint8 channel 1
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            cv::Vec3b color = src.at<cv::Vec3b>(i, j);
            int B = color[0];
            int G = color[1];
            int R = color[2];
            gray.at<uint8_t>(i, j) = (R + G + B) / 3; // 或者其他的 算法
        }

    }

    cv::imshow("src", src);
    cv::imshow("gray", gray);

    // 1. 直接读取 灰度图 直接用这个就行了
    cv::Mat img_gray = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("img_gray", img_gray);


    // 2 读彩图,然后 转为 灰度图
    //src 默认就是读彩图
    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    cv::imshow("img_gray2", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}
