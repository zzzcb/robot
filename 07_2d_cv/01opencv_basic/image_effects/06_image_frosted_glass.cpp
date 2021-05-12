//
// Created by zcb on 5/10/21.
//
/*
 * 图片 毛玻璃效果
 * */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(NULL));

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");

    int offset = 8;


    cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC3);

    int rows = src.rows;
    int cols = src.cols;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            // random x y
            int x = row + rand() % offset;
            int y = col + rand() % offset;
            if (x > rows - 1) {
                x = rows - 1;
            }
            if (y > cols - 1) {
                y = cols - 1;
            }
            cv::Vec3b color = src.at<cv::Vec3b>(x, y);

            dst.at<cv::Vec3b>(row, col) = color;
        }
    }
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}

