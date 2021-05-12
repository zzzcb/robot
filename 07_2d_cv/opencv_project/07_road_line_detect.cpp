//
// Created by zcb on 5/12/21.
//

/*
 * 车道线识别
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void fetchROI(cv::Mat &cannyImg, cv::Mat &roi) {
    int height = cannyImg.rows;

    vector<cv::Point> poly = {cv::Point(200, height), cv::Point(1100, height), cv::Point(560, 280)};
    vector<vector<cv::Point>> polys = {poly};
    cv::fillPoly(roi, polys, cv::Scalar(255));
//    cv::imshow("roi", roi);

    // 与操作 并写入 到 roi
    cv::bitwise_and(cannyImg, roi, roi);
//    cv::imshow("roi", roi);

}

void calcAverageKB(vector<cv::Vec2f> &kbs, cv::Vec2f &kb) {
    float k = 0;
    float b = 0;
    for (int i = 0; i < kbs.size(); ++i) {
        k += kbs[i][0];
        b += kbs[i][1];
    }
    kb[0] = k / kbs.size();
    kb[1] = b / kbs.size();

}

void getLine(float k, float b, float y1, float y2, cv::Vec4i &line) {
    float x1 = (y1 - b) / k;
    float x2 = (y2 - b) / k;

    line[0] = x1;
    line[1] = y1;
    line[2] = x2;
    line[3] = y2;
}

void getLeftRightLine(vector<cv::Vec4i> &lines, vector<cv::Vec4i> &lr_lines) {
    vector<cv::Vec2f> l_kbs;
    vector<cv::Vec2f> r_kbs;

    for (int i = 0; i < lines.size(); ++i) {
        cv::Vec4i ln = lines[i];
        // 分出 左右两条直线
        int x1 = ln[0];
        int y1 = ln[1];
        int x2 = ln[2];
        int y2 = ln[3];
        float k = (y2 - y1) * 1.0 / (x2 - x1) * 1.0;
        float b = y1 - k * x1;

        if (k > 0) { // 右面的直线
            r_kbs.push_back(cv::Vec2f(k, b));
        } else {
            l_kbs.push_back(cv::Vec2f(k, b));
        }
    }

    // 计算 平均 k b
    cv::Vec2f l_kb;
    calcAverageKB(l_kbs, l_kb);
    // 计算 l_line
    cv::Vec4i l_line;
    getLine(l_kb[0], l_kb[1], 720, 360, l_line);

    cv::Vec2f r_kb;
    calcAverageKB(r_kbs, r_kb);
    // 计算 l_line
    cv::Vec4i r_line;
    getLine(r_kb[0], r_kb[1], 720, 360, r_line);

    lr_lines = {l_line, r_line};
}

int main() {
    cv::VideoCapture capture("/home/zcb/cv2/opencv_project/images/road_line.mp4");

    if (capture.isOpened()) {
        // 读取帧
        while (true) {
            cv::Mat frame;
            bool isOk = capture.read(frame);
            if (isOk) {
                // canny 边缘检测
                cv::Mat cannyImg;
                cv::Canny(frame, cannyImg, 50, 100);


                // 提取出 ROI
                cv::Mat roi = cv::Mat::zeros(frame.size(), CV_8UC1);
                fetchROI(cannyImg, roi);

                // 霍夫直线检测
                vector<cv::Vec4i> lines;
                cv::HoughLinesP(roi, lines, 1, CV_PI / 180, 30, 10, 3); //30 是直线由 30个点组成

//                cout << lines.size() << endl;
                // 将检测出来的线 融合 成左右两个线

                vector<cv::Vec4i> lr_lines; // 输出参数
                getLeftRightLine(lines, lr_lines);

                // 左线
                cv::Vec4i l_line = lr_lines[0];
                cv::line(frame, cv::Point(l_line[0], l_line[1]), cv::Point(l_line[2], l_line[3]), cv::Scalar(0, 255, 0),
                         3);

                // 右线
                cv::Vec4i r_line = lr_lines[1];
                cv::line(frame, cv::Point(r_line[0], r_line[1]), cv::Point(r_line[2], r_line[3]),
                         cv::Scalar(0, 255, 255), 3);

                cv::imshow("frame", frame);
                cv::imshow("roi", roi);
            } else {
                break;
            }
            cv::waitKey(50);
        }
    }

    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

