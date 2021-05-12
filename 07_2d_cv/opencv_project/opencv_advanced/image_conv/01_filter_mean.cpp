//
// Created by zcb on 5/11/21.
//

/*
 * 均值滤波 去除噪点,副作用:图像变得模糊
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/itheima_salt.jpg");

    /*
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1) / 9; // 均值滤波
    cv::Mat dst;
    cv::filter2D(src,dst,CV_8UC3,kernel);// CV_8UC3 位置也可以直接写 -1. 让程序自己推断
     */

    // 或者使用封装好的 blur 函数
    cv::Mat dst;
    cv::blur(src,dst,cv::Size(3,3));


    cv::imshow("src",src);
    cv::imshow("dst",dst);



    cv::waitKey();
    cv::destroyAllWindows();

}
