//
// Created by zcb on 5/11/21.
//
/*
 * 拉普拉斯 算子,拉普拉斯变换后增强了图像中灰度突变处的对比度,使图像的细节比原始图像更加清晰
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/hehua.jpg");

    cv::Mat dst;
    cv::Laplacian(src,dst,-1,5); // 5x5

    cv::imshow("src",src);
    cv::imshow("dst",dst);


    cv::waitKey();
    cv::destroyAllWindows();

}
