//
// Created by zcb on 5/11/21.
//
/*
 * 模板匹配
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/zhaonimei.jpg");
    cv::Mat tmpl = cv::imread("/home/zcb/cv2/opencv_extra/images/mei.jpg");


    cv::Mat result;
    cv::matchTemplate(src, tmpl, result, cv::TM_SQDIFF);

    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
//    cv::circle(src, minLoc, 15, cv::Scalar(0, 0, 255), 5);
//    cv::circle(src, maxLoc, 15, cv::Scalar(0, 0, 255), 5);

    // 在原图上 将 模板框起来
    cv::rectangle(src, cv::Rect(minLoc.x, minLoc.y, tmpl.cols, tmpl.rows), cv::Scalar(0, 255, 0), 5);


    cv::imshow("src", src);
    cv::imshow("tmpl", tmpl);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}


