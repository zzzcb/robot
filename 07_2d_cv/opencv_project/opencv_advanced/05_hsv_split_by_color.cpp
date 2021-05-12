//
// Created by zcb on 5/10/21.
//

/*
 * 通过某种颜色范围来分割图片
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/tenis1.jpg");


    cv::Mat hsvImg;
    cv::cvtColor(src, hsvImg, cv::COLOR_BGR2HSV);


    cv::Mat dst;
    cv::Scalar lowerb(30, 43, 46);  // 黄绿色的 范围
    cv::Scalar upperb(60, 255, 255);
    cv::inRange(hsvImg, lowerb, upperb, dst); // 在范围 是255，否则是0

    //cv::imshow("dst",dst); // dst 可以作为一个蒙版

    cv::Mat result;
    src.copyTo(result,dst);
    cv::imshow("src",src);
    cv::imshow("result",result);


    cv::waitKey();
    cv::destroyAllWindows();

}
