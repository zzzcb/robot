//
// Created by zcb on 5/7/21.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    // CV_8UC3 CV  8U(8位的数据) C3(3通道rgb)
    cv::Mat src = cv::Mat::zeros(400, 600, CV_8UC3);
    // 图片size
    cout << src.rows << src.cols << endl;
    // 通道数 channel
    cout << src.channels() <<endl;

    cout << src.size().width << src.size().height << endl;

    // 在图片 中间画一条横向的红色线
    for (int i = 0; i < src.cols; ++i) {
        src.at<cv::Vec3b>(200,i) =cv::Vec3b(0,0,255); // opencv 中是 bgr
    }

    cv::imshow("image",src);
    cv::waitKey();

    return 0;
}

