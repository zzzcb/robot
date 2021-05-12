//
// Created by zcb on 5/11/21.
//
/*
 * 视频处理
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::VideoCapture capture("/home/zcb/cv2/opencv_advanced/images/twotiger.avi");

    // 获取视频的 信息
    int fps = capture.get(cv::CAP_PROP_FPS);
    int width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    int count = capture.get(cv::CAP_PROP_FRAME_COUNT);
    cout << " fps : " << fps << " width : " << width << " height : " << height << " count : " << count;

    // 循环读取帧
    cv::Mat frame;
    while (true) {
        bool isOk = capture.read(frame);
        if (isOk) {
//        cout << "read success"<<endl;
            cv::imshow("frame", frame);

        } else {
//        cout << "read success"<<endl;
            break;
        }
        cv::waitKey(125); // fps:8 ,1000/8 = 125,125毫秒一张图片 // 睡 125ms
    }


    cv::waitKey();
    cv::destroyAllWindows();

}

