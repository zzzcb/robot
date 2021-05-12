//
// Created by zcb on 5/11/21.
//
/*
 *  视频 背景消除
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main() {
    cv::VideoCapture capture("/home/zcb/cv2/opencv_extra/images/vtest.avi");
    if (capture.isOpened()) {
        double fps = capture.get(cv::CAP_PROP_FPS);

        cv::Ptr<cv::BackgroundSubtractorMOG2> mog2 = cv::createBackgroundSubtractorMOG2();

        bool isOk;
        cv::Mat frame; // 读取 一帧
        cv::Mat mask;
        while (true) {
            isOk = capture.read(frame);
            if (isOk) {
                mog2->apply(frame, mask);
                cv::imshow("frame", frame);

                // mask 处理  开操作  ,降噪
                cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
                cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

                cv::imshow("mask", mask);
            } else {
                break;
            }
            cv::waitKey(1000 / fps);
        }
    }

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

