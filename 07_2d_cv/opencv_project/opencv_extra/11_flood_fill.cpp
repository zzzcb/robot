//
// Created by zcb on 5/11/21.
//
/*
 * 泛洪填充
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_extra/images/zp.jpg");


    cv::Point seedPoint(10, 10); // 注水点
    cv::Scalar newVal(0, 0, 255); // 新的颜色
    cv::Rect rect; // 本次填充的矩形区域 输出参数
    cv::Scalar loDiff(10, 10, 10); // 颜色下限
    cv::Scalar upDiff(80, 80, 80); // 颜色上限

    cv::floodFill(src, seedPoint, newVal, &rect, loDiff, upDiff, cv::FLOODFILL_FIXED_RANGE);

    cv::rectangle(src,rect,cv::Scalar(0,255,0));


    cv::imshow("src", src);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

