//
// Created by zcb on 5/11/21.
//

/*
 * 人脸识别
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::CascadeClassifier face = cv::CascadeClassifier(
            "/home/zcb/cv2/opencv_advanced/images/haarcascade_frontalface_default.xml");
    cv::CascadeClassifier eye = cv::CascadeClassifier(
            "/home/zcb/cv2/opencv_advanced/images/haarcascade_eye.xml");

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_advanced/images/lena.jpg");

    std::vector<cv::Rect> faces;
    face.detectMultiScale(src, faces);

    for (int i = 0; i < faces.size(); ++i) {
        cv::rectangle(src, faces[i], cv::Scalar(0, 0, 255));

        // 进一步 检测眼睛
        std::vector<cv::Rect> eyes;
        eye.detectMultiScale(src,eyes);
        for (int j = 0; j < eyes.size(); ++j) {
            cv::rectangle(src,eyes[j],cv::Scalar(255,0,0));
        }
    }

    cv::imshow("src",src);


    cv::waitKey();
    cv::destroyAllWindows();

}


