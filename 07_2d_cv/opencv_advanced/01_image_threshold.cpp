//
// Created by zcb on 5/10/21.
//

/*
 * 图片 二值化, 简单阈值
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void callback(int pos, void *userdata) {

    cv::Mat src = *(cv::Mat *) userdata;
    cv::Mat dst;
    cv::threshold(src, dst, pos, 255, cv::THRESH_BINARY);
    cv::imshow("dst", dst);
}


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/car.jpg", cv::IMREAD_GRAYSCALE);

    cv::imshow("src", src);

    int pos = 10; // 默认初始的数值
    cv::createTrackbar("thresh_val", "src", &pos, 255, callback, &src);


    cv::waitKey();
    cv::destroyAllWindows();

}














