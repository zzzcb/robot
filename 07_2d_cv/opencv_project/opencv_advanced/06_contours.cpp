//
// Created by zcb on 5/11/21.
//

/*
 * 查找轮廓，绘制轮廓
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/shape.jpg");

    // 彩图 -> 灰度图
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 灰度图 二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // get info from contours
    /*
    for (int i = 0; i < contours.size(); ++i) {
        // 轮廓面积 
        double area = cv::contourArea(contours[i]);
        // 轮廓周长
        double arcLen = cv::arcLength(contours[i], true);
        cout << "area " << area << " arc_len " << arcLen << endl;

        // 轮廓的外切矩形
        cv::Rect rect = cv::boundingRect(contours[i]);
        cv::rectangle(src, rect, cv::Scalar(0, 0, 255));

        // 轮廓的外切圆形
        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contours[i], center, radius);
        cv::circle(src, center, radius, cv::Scalar(255, 0, 0));
    }*/



    // draw contours
    cv::drawContours(src, contours, -1, cv::Scalar(0, 0, 0), 5); // 在src 上 绘制 contours

    cv::imshow("src", src);


    cv::waitKey();
    cv::destroyAllWindows();

}



