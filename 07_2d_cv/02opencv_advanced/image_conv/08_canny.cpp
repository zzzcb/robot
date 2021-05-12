//
// Created by zcb on 5/11/21.
//


/*
 * Canny 边缘检测, canny 是一个多阶段算法,http://robot.czxy.com/docs/opencv/03_opencv_advance2/02_juanji/#canny
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/hehua.jpg",cv::IMREAD_GRAYSCALE);



    cv::Mat dst;
    cv::Canny(src,dst,50,100); // lower:50 upper:100


    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}