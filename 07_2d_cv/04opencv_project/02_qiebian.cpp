//
// Created by zcb on 5/12/21.
//

/*
 * 图片 切边
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

// ROI  region of interest  感兴趣的区域
cv::Rect fetchROI(cv::Mat &src) {
    // gray
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // binary
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
//    cv::imshow("binary",binary);

    // 找出最大的轮廓
    vector<vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    int max_idx = 0;
    double max_area = -1;
    for (int i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > max_area) {
            max_idx = i;
            max_area = area;
        }
    }
    // 最大轮廓是 contours[max_idx]
    //cv::drawContours(src,contours,max_idx,cv::Scalar(0,0,255),5);
    // 最大轮廓的 外切矩形
    cv::Rect rect = cv::boundingRect(contours[max_idx]);
    //cout << rect << endl;


    return rect;
}


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_project/images/01_qiebian.jpg");

    // 获取 感兴趣的 矩形
    cv::Rect rect = fetchROI(src);

    // 截取原图
    cv::Mat dst;
    dst = src(rect);

    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}