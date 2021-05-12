//
// Created by zcb on 5/10/21.
//

/*
 * 图片 浮雕效果
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg", cv::IMREAD_GRAYSCALE);


    cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC1);

    int rows = src.rows;
    int cols = src.cols;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols - 1; ++col) {

            uint8_t gray0 = src.at<uint8_t>(row, col);
            uint8_t gray1 = src.at<uint8_t>(row, col + 1);
            uint8_t ret = 150 + gray1 - gray0;
            dst.at<uint8_t>(row, col) = ret;
        }
    }
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}
