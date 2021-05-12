//
// Created by zcb on 5/10/21.
//
/*
 * 调节图片的亮度
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int limit(int val) {
    if (val > 255) return 255;
    if (val < 0) return 0;
    return val;
}


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg");


    cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);

    int offset = 50;
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            cv::Vec3b color = src.at<cv::Vec3b>(i, j);
            int b = limit(color[0] + offset);
            int g = limit(color[1] + offset);
            int r = limit(color[2] + offset);

            dst.at<cv::Vec3b>(i, j) = cv::Vec3b(b, g, r);

        }
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();

}
