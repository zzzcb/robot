//
// Created by zcb on 5/11/21.
//

/*
 *  图像的 闭操作，先膨胀，再腐蚀
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/morph-closing.jpg");

    // 可以使用封装好的函数
    cv::Mat dst;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(src,dst,cv::MORPH_CLOSE,kernel);
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
