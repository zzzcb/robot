//
// Created by zcb on 5/10/21.
//

/*
 * 计算 灰度 图片的 直方图数据
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/itheima.jpg", cv::IMREAD_GRAYSCALE);

    cv::Mat hist;
    const int histSize = 256;
    float range[] = {0, 255};
    const float *histRanges = range;

    // 1个图片 0 通道 1维度
    cv::calcHist(&src, 1, 0, cv::Mat(), hist, 1, &histSize, &histRanges);

//    cout << hist << endl;
    // 绘制 直方图  h: 500 w : 256*2
    int height = 500;
    int width = 256 * 2;
    // 将数据归一化
    cv::Mat dstHist;
    cv::normalize(hist, dstHist, 0, height, cv::NORM_MINMAX);
//    cout << dstHist << endl;

    // 绘制 线段
    cv::Mat picture = cv::Mat::zeros(height, width, CV_8UC3);
    for (int i = 0; i < 256; ++i) {
        cv::line(picture, cv::Point(2 * i, height), cv::Point(2 * i, height - dstHist.at<float>(i)),
                 cv::Scalar(0, 0, 255));
    }
    cv::imshow("picture", picture);

    cv::waitKey();
    cv::destroyAllWindows();

}
