//
// Created by zcb on 5/8/21.
//
/*
 * 图片 旋转(使用 矩阵 )
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");
    cv::imshow("lena", src);


    // 旋转 矩阵 绕左上角 旋转 45度
    cv::Mat rotate_m = (cv::Mat_<float>(2, 3) << cos(M_PI / 4), -sin(M_PI / 4), 0
            , sin(M_PI / 4), cos(M_PI / 4), 0);

    // 绕 中心点  旋转 45 度
    // 得到 旋转矩阵
    // 1 平移图片 至原点
    cv::Mat T1 = (cv::Mat_<float>(3, 3) << 1, 0, src.cols / 2,
            0, 1, src.cols / 2,
            0, 0, 1);

    // 2 旋转图片
    cv::Mat R = (cv::Mat_<float>(3, 3) << cos(M_PI / 4), -sin(M_PI / 4), 0,
            sin(M_PI / 4), cos(M_PI / 4), 0,
            0, 0, 1);
    // 3 平移回去
    cv::Mat T2 = (cv::Mat_<float>(3, 3) << 1, 0, -src.cols / 2,
            0, 1, -src.cols / 2,
            0, 0, 1);

    cv::Mat T = T1 * R * T2;
    cv::Mat rotate_m2 = T.rowRange(0, 2);// [0,2)


    cv::Mat dst;
    cv::warpAffine(src, dst, rotate_m, cv::Size());
    cv::imshow("dst", dst);


    cv::Mat dst2;
    cv::warpAffine(src, dst2, rotate_m2, cv::Size());
    cv::imshow("dst2", dst2);


    // 更简便的方法  以后直接用它即可
    cv::Mat rotate_m3 = cv::getRotationMatrix2D(cv::Point2f(src.rows / 2, src.cols / 2), 45, 1.0);
    cv::Mat dst3;
    cv::warpAffine(src, dst3, rotate_m3, cv::Size());
    cv::imshow("dst3", dst3);

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
