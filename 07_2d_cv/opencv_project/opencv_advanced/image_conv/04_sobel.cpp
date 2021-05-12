//
// Created by zcb on 5/11/21.
//
/*
 * sobel 算子,用于边缘检测
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/brain.jpg");

    cv::Mat x_sobel;
    cv::Sobel(src,x_sobel,-1,1,0);


    cv::Mat y_sobel;
    cv::Sobel(src,y_sobel,-1,0,1); // 不可以同时 x,y

    cv::Mat xy_sobel;
    cv::add(x_sobel,y_sobel,xy_sobel);


    cv::imshow("src",src);

    cv::imshow("x_sobel",x_sobel);
    cv::imshow("y_sobel",y_sobel);
    cv::imshow("xy_sobel",xy_sobel);


    cv::waitKey();
    cv::destroyAllWindows();

}

