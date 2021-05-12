//
// Created by zcb on 5/11/21.
//

/*
 * scharr 改进版 scharr
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/brain.jpg");

    cv::Mat x_scharr;
    cv::Scharr(src, x_scharr, -1, 1, 0);


    cv::Mat y_scharr;
    cv::Scharr(src, y_scharr, -1, 0, 1); // 不可以同时 x,y

    cv::Mat xy_scharr;
    cv::add(x_scharr, y_scharr, xy_scharr);


    cv::imshow("src", src);

    cv::imshow("x_scharr", x_scharr);
    cv::imshow("y_scharr", y_scharr);
    cv::imshow("xy_scharr", xy_scharr);


    cv::waitKey();
    cv::destroyAllWindows();

}
