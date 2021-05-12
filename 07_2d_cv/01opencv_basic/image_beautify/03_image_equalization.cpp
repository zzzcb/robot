//
// Created by zcb on 5/10/21.
//

/*
 * 直方图 均衡化
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg", cv::IMREAD_GRAYSCALE);


    cv::Mat dst;
    cv::equalizeHist(src, dst);
    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}
