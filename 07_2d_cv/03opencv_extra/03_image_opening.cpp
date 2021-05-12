//
// Created by zcb on 5/11/21.
//
/*
 *  图像的 开操作，先腐蚀，再膨胀
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/morph-opening.jpg");

    /*
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::erode(src, dst, kernel);

    cv::Mat dst2;
    cv::dilate(dst,dst2,kernel);

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::imshow("dst2", dst2);
     */

    // 可以使用封装好的函数
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(src,dst,cv::MORPH_OPEN,kernel);
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

