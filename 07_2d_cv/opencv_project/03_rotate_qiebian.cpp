//
// Created by zcb on 5/12/21.
//

/*
 * 图片 先旋转再切边
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

vector<cv::Point> getMaxContour(cv::Mat &src) {
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

    return contours[max_idx];
}


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_project/images/02_qiebian.jpg");
    vector<cv::Point> contour = getMaxContour(src);
    // 得到 最小包围矩形 
    cv::RotatedRect rotated_rect = cv::minAreaRect(contour);
    double angle = rotated_rect.angle;
    cv::Point2f center = rotated_rect.center;

    // 得到旋转矩阵
    cv::Mat M = cv::getRotationMatrix2D(center, 90 + angle, 1.0);
    cv::Mat dst1;
    cv::warpAffine(src, dst1, M, cv::Size());

    vector<cv::Point> contour2 = getMaxContour(dst1);

    cv::Rect rect = cv::boundingRect(contour2);
    cv::Mat dst2 = dst1(rect);

    cv::imshow("src", src);
    cv::imshow("dst1", dst1);
    cv::imshow("dst2", dst2);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}