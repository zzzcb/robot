//
// Created by zcb on 5/11/21.
//
/*
 *  霍夫直线
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/weiqi.jpg");

    cv::Mat gray;
    cv::cvtColor(src,gray,cv::COLOR_BGR2GRAY);

    // 二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | CV_THRESH_OTSU);
//    cv::imshow("binary",binary);

    std::vector<cv::Vec4i> lines;

    double rho = 1; //精度控制 每隔几个像素 计算一下
    double theta = 3.14 / 180;  //精度控制 每隔多少theta 查看一下是否相交
    double threshold = 15; // 相交的点的数量
    double minLineLength = 30;
    double maxLineGap = 10;

    cv::HoughLinesP(binary, lines, rho, theta, threshold, minLineLength, maxLineGap);
    for (int i = 0; i < lines.size(); ++i) {
        // 画出每条直线
        cv::Point pt1(lines[i][0],lines[i][1]);
        cv::Point pt2(lines[i][2],lines[i][3]);
        cv::line(src,pt1,pt2,cv::Scalar(0,0,255));

    }
    cv::imshow("src",src);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

