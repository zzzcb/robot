//
// Created by zcb on 5/8/21.
//

/*
 * 图片 位移(使用 矩阵 )
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");
    cv::imshow("lena", src);


    // 位移 矩阵
    cv::Mat shift_m = (cv::Mat_<float>(2,3) << 1,0,30
                                              ,0,1,50);

    cv::Mat dst;
    cv::warpAffine(src,dst,shift_m,cv::Size());

    cv::imshow("dst", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
