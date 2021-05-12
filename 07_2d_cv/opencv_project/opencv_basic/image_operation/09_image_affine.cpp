//
// Created by zcb on 5/8/21.
//

/*
 * 图片 仿射变换
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg");

    // 矩阵
    // 图片的三个点  左上角 ，左下角 右上角
    cv::Point2f srcs[] = {cv::Point2f(0, 0), cv::Point2f(0, src.rows - 1), cv::Point2f(src.cols - 1, 0),};
    cv::Point2f dsts[] = {cv::Point2f(100, 100), cv::Point2f(200, src.rows - 100), cv::Point2f(src.cols - 100, 100),};
    cv::Mat m = cv::getAffineTransform(srcs,dsts);

    cv::Mat dst;
    cv::warpAffine(src,dst,m,cv::Size());

    cv::imshow("src",src);
    cv::imshow("dst",dst);



    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
