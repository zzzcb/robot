//
// Created by zcb on 5/7/21.
//
/*
 * 图片剪切
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");
    cv::imshow("lena", src);

    cv::Rect rect(50, 50, 100, 100);
    cv::Mat ret = src(rect);// 剪切 ret 是src的一个引用，如果修改ret, src 也会跟着变
    cv::imshow("cut", ret);

    // 修改 ret
    for (int i = 0; i < 50; ++i) {
        ret.at<cv::Vec3b>(10, i) = cv::Vec3b(0, 0, 255);
    }
    cv::imshow("cut_after", ret);
    cv::imshow("src", src);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}






