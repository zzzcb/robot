//
// Created by zcb on 5/12/21.
//
/*
 * 检测 答题卡上的 空
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_project/images/engline.jpg");

    // gray
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // binary
    cv::Mat binary;
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    // 删除所有的文字 ,只保留直线 （因为L l 都可能别识别为直线）可以采用形态学 开操作
    cv::Mat dst1;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(21, 1));
    cv::morphologyEx(binary, dst1, cv::MORPH_OPEN, kernel);
    //cv::imshow("binary",binary);
    //cv::imshow("dst1",dst1);

    // 进行霍夫直线检测
    vector<cv::Vec4i> lines;
    cv::HoughLinesP(dst1, lines, 1, CV_PI / 180, 30, 20, 20);
    for (int i = 0; i < lines.size(); ++i) {
        cv::Vec4i l = lines[i];
        cv::line(src,cv::Point(l[0],l[1]),cv::Point(l[2],l[3]),cv::Scalar(0,0,255),3);
    }
    cv::imshow("src",src);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
