//
// Created by zcb on 5/10/21.
//

/*
 * 图片 二值化, 自适应阈值，针对不同的位置采用 不同的阈值
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/thresh1.jpg", cv::IMREAD_GRAYSCALE);


    cv::Mat dst;
    cv::adaptiveThreshold(src,dst,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY_INV,13,1);// 13 x 13

    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}














