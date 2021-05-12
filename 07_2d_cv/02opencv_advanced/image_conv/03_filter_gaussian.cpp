//
// Created by zcb on 5/11/21.
//
/*
 * 高斯模糊,其实就是 卷积核是 加权的，中间的权重高，外面的权重低
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/itheima_salt.jpg");


    cv::Mat dst;
    cv::GaussianBlur(src,dst,cv::Size(3,3),5); // 3 x 3


    cv::imshow("src",src);
    cv::imshow("dst",dst);


    cv::waitKey();
    cv::destroyAllWindows();

}

