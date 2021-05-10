//
// Created by zcb on 5/8/21.
//

/*
 * 图片 缩放
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");
    cv::imshow("lena", src);

    float ratio = 1.5;
    //cv::Size dstSize(src.size().width*ratio,src.size().height*ratio);
    cv::Size dstSize(src.cols * ratio, src.rows * ratio);

    cv::Mat dst;
    cv::resize(src, dst, dstSize);

    cv::imshow("dst", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
