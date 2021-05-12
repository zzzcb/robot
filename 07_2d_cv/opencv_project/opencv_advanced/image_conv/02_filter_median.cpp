//
// Created by zcb on 5/11/21.
//

/*
 * 中值滤波 去除噪点 处理椒盐噪声效果会比较好,但是也不可避免的会导致图像模糊
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/itheima_salt.jpg");


    cv::Mat dst;
    cv::medianBlur(src,dst,3); // 3 x 3


    cv::imshow("src",src);
    cv::imshow("dst",dst);


    cv::waitKey();
    cv::destroyAllWindows();

}
