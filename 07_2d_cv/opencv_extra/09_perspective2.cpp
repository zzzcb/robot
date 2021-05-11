//
// Created by zcb on 5/11/21.
//
/*
 * 透视变换,程序提取 原图的四个点
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/zhengjianzhao.png");


    // 灰度
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 二值化
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    vector<vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 找出面积最大的 contour
    int idx = 0;
    int max_area = -1;
    for (int i = 0; i < contours.size(); ++i) {
        vector<cv::Point> contour = contours[i];
        double area = cv::contourArea(contour);
        if (area > max_area) {
            max_area = area;
            idx = i;
        }
    }
    cv::drawContours(src, contours, idx, cv::Scalar(0, 0, 255));

    // 使用 多边形拟合 这个轮廓
    vector<cv::Point> approxCurve;
    cv::approxPolyDP(contours[idx], approxCurve, 10, true); //10 是阈值
    //cout << approxCurve << endl;
    // 为了使用 drawContours ,将 approxCurve 包装成 temp_contours
    //vector<vector<cv::Point>> temp_contours = {approxCurve};
    //cv::drawContours(src, temp_contours, 0, cv::Scalar(0, 255, 0));


    cv::Mat dst;
    std::vector<cv::Point2f> srcPoints = {approxCurve[1], approxCurve[0], approxCurve[2], approxCurve[3]};
    std::vector<cv::Point2f> dstPoints = {cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(0, 600),
                                          cv::Point2f(480, 600)};
    cv::Mat M = cv::getPerspectiveTransform(srcPoints, dstPoints);
    // M 是 变换矩阵
    cv::warpPerspective(src, dst, M, cv::Size(480, 600));

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

