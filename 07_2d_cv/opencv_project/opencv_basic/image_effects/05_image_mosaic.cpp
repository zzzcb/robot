//
// Created by zcb on 5/10/21.
//
/*
 * 图片 马赛克
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");


    int offset = 32;

//    cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC3);
    for (int row = 0; row < src.rows; ++row) {
        for (int col = 0; col < src.cols; ++col) {

            // 每 4x4 处理一次
            if (row % offset == 0 && col % offset == 0) {
                cv::Vec3b color = src.at<cv::Vec3b>(row, col);
                for (int i = 0; i < offset; ++i) {
                    for (int j = 0; j < offset; ++j) {
                        if (row + i > src.rows - 1 || col + j > src.cols - 1) {
                            continue;
                        }
                        src.at<cv::Vec3b>(row + i, col + j) = color;
                    }
                }
            }
        }
    }

    cv::imshow("src", src);


    cv::waitKey();
    cv::destroyAllWindows();

}
