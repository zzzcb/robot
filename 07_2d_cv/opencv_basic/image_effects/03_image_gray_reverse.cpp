//
// Created by zcb on 5/8/21.
//
/*
 * 灰度图 反转
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg",cv::IMREAD_GRAYSCALE);

    cv::Mat dst = cv::Mat::zeros(src.size(),CV_8UC1);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            dst.at<uint8_t >(i,j) = 255 - src.at<uint8_t >(i,j);
        }
    }
    cv::imshow("src",src);
    cv::imshow("dst",dst);



    cv::waitKey();
    cv::destroyAllWindows();

}
