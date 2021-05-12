//
// Created by zcb on 5/7/21.
//
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::string pwd = "/home/zcb/cv2/opencv_basic";

    // CV_8UC3 CV  8U(8位的数据) C3(3通道rgb)
    cv::Mat src = cv::Mat::zeros(400, 600, CV_8UC3);
    std::cout << src.size().width << " ";
    std::cout << src.size().height << std::endl;


    cv::imwrite(pwd+"/zcb.jpg",src);

    return 0;
}



