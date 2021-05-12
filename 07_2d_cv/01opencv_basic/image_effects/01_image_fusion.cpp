//
// Created by zcb on 5/8/21.
//

/*
 * 图像融合 fusion
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src1 = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg");
    cv::Mat src2 = cv::imread("/home/zcb/cv2/opencv_basic/images/tony.jpg");

    cv::imshow("src1", src1);
    cv::imshow("src2", src2);

    cv::Mat dst;
    cv::addWeighted(src1,0.3,src2,0.7,0,dst); // 最后一个参数是一个偏移量 offset,融合之后加的值

    cv::imshow("fusion",dst);

    cv::waitKey();
    cv::destroyAllWindows();

}
