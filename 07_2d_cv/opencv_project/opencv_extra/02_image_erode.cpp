//
// Created by zcb on 5/11/21.
//
/*
 *  图像的腐蚀
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/morph-j.jpg");


    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::erode(src, dst, kernel);

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

