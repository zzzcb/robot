//
// Created by zcb on 5/11/21.
//
/*
 * 透视变换
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

/*
pt1 = (120,90)# 左上角
pt2 = (350,90)# 右上角
pt3 = (60,470)# 左下角
pt4 = (430,470)# 右下角
*/
int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/zhengjianzhao.png");


    cv::Mat dst;

    std::vector<cv::Point2f> srcPoints = {cv::Point2f(120, 90), cv::Point2f(350, 90), cv::Point2f(60, 470),
                                          cv::Point2f(430, 470),};
    std::vector<cv::Point2f> dstPoints = {cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(0, 600),
                                          cv::Point2f(480, 600)};
    cv::Mat M = cv::getPerspectiveTransform(srcPoints, dstPoints);
    // M 是 变换矩阵
    cv::warpPerspective(src, dst, M, cv::Size(480,600));

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

