//
// Created by zcb on 5/11/21.
//

/*
 *  霍夫圆, 不需要使用二值图
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/weiqi.jpg");

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Vec3f> circles;
    int method = cv::HOUGH_GRADIENT;
    double dp = 1;
    double minDist = 20; // 圆之间的距离 gap
    double param1 = 100; // canny 的阈值上限
    double param2 = 25; // 累加器的阈值
    double minRadius = 0;
    double maxRadius = 20;
    cv::HoughCircles(gray, circles, method, dp, minDist, param1, param2, minRadius, maxRadius);
    for (int i = 0; i < circles.size(); ++i) {
        // 画出 圆
        cv::circle(src, cv::Point(circles[i][0], circles[i][1]), circles[i][2], cv::Scalar(0, 0, 255));

    }
    cv::imshow("src", src);
    cv::imshow("gray",gray);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

