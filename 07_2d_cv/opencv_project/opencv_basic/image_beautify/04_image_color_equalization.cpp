//
// Created by zcb on 5/10/21.
//
/*
 * 彩色 的均衡化  
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg");


    cv::Mat channels[3];
    cv::split(src, channels);
    
    
    
    cv::equalizeHist(channels[0],channels[0]);
    cv::equalizeHist(channels[1],channels[1]);
    cv::equalizeHist(channels[2],channels[2]);
    
    cv::Mat dst;
    cv::merge(channels,3,dst);
    
    cv::imshow("src",src);
    cv::imshow("dst",dst);
   
    
   
    cv::waitKey();
    cv::destroyAllWindows();

}
