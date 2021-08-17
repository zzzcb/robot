//
// Created by zcb on 7/8/21.
//
/*
 * 相机内参标定
 * 这里的功能是收集图片,为后面的标定做准备
 */

// ros
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>// 将ros image 转换为 cv 的格式

// opencv
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <unistd.h>

int cnt = 0;

void save_image(const sensor_msgs::ImageConstPtr &msg) {
    cv_bridge::CvImagePtr imagePtr;
    try {
        imagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
        ROS_ERROR_STREAM("error info" << e.what());
        return;
    }

    cv::imshow("image", imagePtr->image);
    cv::waitKey(0);// 用户按键之后才会保存
    cv::imwrite("pic" + std::to_string(cnt++) + ".png", imagePtr->image);
    std::cout << "成功保存" << cnt << " 张图片" << std::endl;
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
