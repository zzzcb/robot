//
// Created by zcb on 5/11/21.
//
/*
 *  去除验证码的干扰线，使用开操作:先腐蚀 再膨胀
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/yanzhengma.jpg",cv::IMREAD_GRAYSCALE);


    // 二值化
    cv::Mat binary;
    cv::threshold(src,binary,0,255,cv::THRESH_BINARY_INV|CV_THRESH_OTSU);
//    cv::imshow("binary",binary);

    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::morphologyEx(binary,dst,cv::MORPH_OPEN,kernel);
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

