//
// Created by zcb on 5/10/21.
//

/*
 * hsv : h: 色调 s:饱和度  v:明度
 * hsv 有rgb不可比拟的作用,
 * 例如：
 *    判断一个颜色是什么颜色如果用rgb,不太好判断，而使用hsv 只需要h即可
 *    再如,判断一个图片是白天还是夜里,使用rgb无法判断,使用hsv只需要判断 v 即可
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

float calcAverageBrightness(cv::Mat img) {

    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);


    cv::Mat channels[3];
    cv::split(hsv, channels);

    cv::Mat vChannel = channels[2];

    // 计算平均亮度
    float s = 0;
    for (int row = 0; row < vChannel.rows; ++row) {
        for (int col = 0; col < vChannel.cols; ++col) {
            s += vChannel.at<uint8_t >(row, col);
        }
    }
    return s / (vChannel.rows * vChannel.cols);
}


int main() {

    cv::Mat day = cv::imread("/home/zcb/cv2/opencv_advanced/images/day.jpg");
    cv::Mat night = cv::imread("/home/zcb/cv2/opencv_advanced/images/night.jpg");

    cv::imshow("day", day);
    cv::imshow("night", night);

    cout << "day: " << calcAverageBrightness(day) << endl;
    cout << "night: " << calcAverageBrightness(night) << endl;


    cv::waitKey();
    cv::destroyAllWindows();

}
