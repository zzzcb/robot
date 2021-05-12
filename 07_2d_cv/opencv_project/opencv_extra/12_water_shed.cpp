//
// Created by zcb on 5/11/21.
//
/*
 * 图像分水岭   http://robot.czxy.com/docs/opencv/04_cpp_opencv/13_watershed/#_1
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

cv::Mat src;
int n = 1; // 标记中的数值 必须大于1

void callbk(int event, int x, int y, int flags, void *userdata) {

    cv::Mat markers = *(cv::Mat *) userdata;
    // 左键按下
    if (event == cv::EVENT_LBUTTONDOWN) {
        // 打 标记
        cv::circle(markers, cv::Point(x, y), 30, cv::Scalar(n++), -1); // 什么图形都可以
    } else if (event == cv::EVENT_RBUTTONDOWN) {
        //右键按下 开始分水岭算法
        cv::watershed(src, markers);

        // 展示
        vector<cv::Vec3b> colors = {cv::Vec3b(0, 255, 0), cv::Vec3b(0, 255, 255)};
        cv::Mat display = cv::Mat::zeros(src.size(), CV_8UC3);
        for (int i = 0; i < markers.rows; ++i) {
            for (int j = 0; j < markers.cols; ++j) {
                int label = markers.at<int>(i, j);
                if (label > 0 && label < n) {
                    display.at<cv::Vec3b>(i, j) = colors[label - 1];
                } else {
                    // label == -1  // 代表的是 边界
                    display.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 255);
                }
            }
        }
        cv::imshow("display", display);

    }


}


int main() {
    src = cv::imread("/home/zcb/cv2/opencv_extra/images/wan.png");

    // gray
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);


    cv::imshow("gray", gray);

    // markers
    cv::Mat markers = cv::Mat::zeros(gray.size(), CV_32S);// 有符号的 int
    cv::setMouseCallback("gray", callbk, &markers);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

