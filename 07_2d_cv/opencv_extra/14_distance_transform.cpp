//
// Created by zcb on 5/11/21.
//
/**
距离变换: 用于计算图像中每一个非零点 和 距离自己最近的零点 之间的距离,
        方法输出的信息为距离而不是颜色值，图像上越亮的点，代表了离零点的距离越远。
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv) {
    cv::Mat gray = imread("/home/zcb/cv2/opencv_extra/images/shape.jpg", cv::IMREAD_GRAYSCALE);

    cv::imshow("gray", gray);
    // 将图片转成二值图像
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    // imshow("binary", binary);

    // 距离变换
    cv::Mat distanceImg;
    cv::distanceTransform(binary, distanceImg, cv::DIST_L2, 3);// 3 类似于 卷积核的大小


    // 此时 distanceImg 中的距离是浮点数,需要将数据归一化到0～1之间,然后展示
    cv::normalize(distanceImg, distanceImg, 0, 1.0, cv::NORM_MINMAX);

    imshow("distance", distanceImg);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

