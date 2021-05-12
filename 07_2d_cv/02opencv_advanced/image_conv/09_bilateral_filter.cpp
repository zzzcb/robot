//
// Created by zcb on 5/11/21.
//

/*
 * 双边滤波 ,主要用于磨皮
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/timg.jpg");


    cv::Mat dst;

    cv::bilateralFilter(src,dst,10,50,30);


    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}