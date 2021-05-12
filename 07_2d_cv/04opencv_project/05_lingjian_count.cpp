//
// Created by zcb on 5/12/21.
//
/*
 * 零件计数
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_project/images/lingjian.png");

    // gray
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // binary
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 距离变换 
    cv::Mat dst1;
    cv::distanceTransform(binary, dst1, cv::DIST_C, 3);
    cv::normalize(dst1,dst1,0,1,cv::NORM_MINMAX);
    cv::threshold(dst1,dst1,0.5,1,cv::THRESH_BINARY);

    cv::imshow("src", src);
    cv::imshow("binary", binary);
    cv::imshow("dst1", dst1);

    // 轮廓
    vector<vector<cv::Point>> contours;
    dst1.convertTo(dst1,CV_8UC1); // 不然会报错
    cv::findContours(dst1,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);

    cout << "count : " << contours.size() << endl;


    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

