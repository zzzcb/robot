//
// Created by zcb on 7/10/21.
//
/*
 * 改变机械臂的位置,对固定的标定板进行拍照
 */
// ros
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>// 将ros image 转换为 cv 的格式

// opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <unistd.h>

using namespace std;

int cnt = 0;

void findCorners(cv::Mat &src, const cv::Size &patternSize, bool &isFound, vector<cv::Point2f> &corners) {
    // src,patternSize 传入参数
    // isFound,corners 传出参数

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    isFound = cv::findChessboardCorners(gray, patternSize, corners);
    if (isFound) {
        // 3 优化角点位置（只用于棋盘格）
        // 提高角点精度
        cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1);
        cv::cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
    }

}

void save_image(const sensor_msgs::ImageConstPtr &msg) {

    cv_bridge::CvImagePtr imagePtr;
    try {
        imagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
        ROS_ERROR_STREAM("error info" << e.what());
        return;
    }
    cv::Mat tempImg;
    imagePtr->image.copyTo(tempImg);

    bool isFound;
    vector<cv::Point2f> corners;
    findCorners(tempImg, cv::Size(6, 9), isFound, corners);
    cv::drawChessboardCorners(tempImg, cv::Size(6, 9), corners, isFound);

    cv::imshow("image", tempImg);
    std::cout << "按s保存图片(q退出)" << std::endl;

    int ret = cv::waitKey(1000); // 1s
    if (ret == 'q') {
        exit(0);
    } else if (ret == 's') { // s 保存
        cv::imwrite("pic" + std::to_string(cnt++) + ".png", imagePtr->image);
        std::cout << "成功保存" << cnt << " 张图片" << std::endl;
    }
}

int main(int argc, char **argv) {

    std::string nodeName = "collect_image";
    ros::init(argc, argv, nodeName, ros::init_options::AnonymousName);
    ros::NodeHandle node;

    // 订阅ros 中的 /camera/color/image_raw  topic,就可以用opencv处理保存图片了
    image_transport::ImageTransport it(node);
    const image_transport::Subscriber &subscriber = it.subscribe("/camera/color/image_raw", 1, save_image);

    ros::spin();

    return 0;
}
