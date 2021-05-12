//
// Created by zcb on 5/10/21.
//
/*
 * 采用日本人大津提出的算法,又称作最大类间方差法,被认为是图像分割中阈值选取的最佳算法,采用这种算法的好处是执行效率高!
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/car.jpg", cv::IMREAD_GRAYSCALE);


    cv::Mat dst;
    double thresh_val = cv::threshold(src,dst,0,255,cv::THRESH_BINARY|cv::THRESH_OTSU); // 初始阈值 随便写，这里写的是 0

    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}

