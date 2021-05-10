//
// Created by zcb on 5/10/21.
//
/*
 * 图片 绘制  图形 文字
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");

    // 直线
    cv::line(src, cv::Point(100, 100), cv::Point(300, 100), cv::Scalar(0, 0, 255), 5);

    // 矩形
    cv::Rect rect(50,50,110,220); // (50,50) width:110,height:220
    cv::rectangle(src,rect,cv::Scalar(0,255,0),5);

    // 圆形
    cv::circle(src,cv::Point(150,150),33,cv::Scalar(255,0,0),-1); // thickness 是负数就是 填充效果

    // 文字
    cv::putText(src,"robot",cv::Point(30,30),cv::FONT_HERSHEY_COMPLEX,1.0,cv::Scalar(0,0,255));





    cv::imshow("src", src);
//    cv::imshow("dst", dst);


    cv::waitKey();
    cv::destroyAllWindows();

}

