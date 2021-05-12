//
// Created by zcb on 5/11/21.
//

/*
 * 图像的锐化
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/hehua.jpg");


    int k = 1;
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << -k, -k, -k, -k, 8 * k + 1, -k, -k, -k, -k);

    cv::Mat dst;
    cv::filter2D(src,dst,-1,kernel);

    cv::imshow("src", src);
    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}
