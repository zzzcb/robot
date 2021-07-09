//
// Created by zcb on 7/8/21.
//

// ros
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>// 将ros image 转换为 cv 的格式

// opencv
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <unistd.h>

double camera_table_x, camera_table_y, camera_table_z; // 在相机坐标系下 table上表面中心点的坐标
int ux = -1; // table 中心点在像素坐标系中的坐标
int uy = -1;

void imageProcess(const cv::Mat &src) {
    cv::Mat gray;
    //1.bgr -> gray
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    //cv::imshow("gray", gray);

    //2.高斯滤波
    cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0.1);// 0.1:标准差

    //3 canny 提取
    cv::Mat cannyOutput;
    cv::Canny(gray, cannyOutput, 30, 30 * 3); // 阈值设置：两个阈值成比例3：1或2：1

    //cv::imshow("canny", cannyOutput);

    //4 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(cannyOutput, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //在 src上绘制轮廓点的轮廓,红色
    //cv::drawContours(src, contours, -1, cv::Scalar(0, 0, 255), 5); 
    //cv::imshow("contours", src);

    //5 依据查找的轮廓点生成一个矩形
    cv::Rect rect = cv::boundingRect(contours[0]);

    cv::Point2f cpt; // 该矩形的中心点
    cpt.x = rect.x + rect.width / 2.0;
    cpt.y = rect.y + rect.height / 2.0;

    cv::Mat new_pic = cv::Mat::zeros(src.size(), CV_8UC3);//在一个新的图片上 绘制估计出来的矩形
    cv::rectangle(new_pic, rect, cv::Scalar(255, 0, 0));

    cv::circle(new_pic, cpt, 5, cv::Scalar(0, 0, 255), -1);

    char text[32];
    sprintf(text, "x:%.2f y:%.2f", cpt.x, cpt.y);
    cv::putText(new_pic, text, cpt, cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 255));

    //cv::imshow("new pic", new_pic);

    //6 已知 桌子在世界中的长宽高为0.4, 已知相机的图片像素是640x480 ，求桌子中心在相机坐标系中的实际坐标(这里只能求yz,x是深度(kinect x 朝向))
    double dx = 0.4 / rect.width;// x方向单位像素的长度
    double dy = 0.4 / rect.height;//y方向单位像素的长度

    double y = (320 - cpt.x) * dx;  // 桌子中心在 相机坐标系下的y坐标
    double z = (240 - cpt.y) * dy; // 桌子中心在 相机坐标系下的y坐标
    // 具体的x 坐标需要使用 从深度图中读取
    //std::cout << "桌子中心在相机坐标系下的坐标位置是: y " << y << " (m) " << " z " << z << " (m)" << std::endl;
    camera_table_y = y;
    camera_table_z = z;
    ux = (int) cpt.x;
    uy = (int) cpt.y;

    //cv::waitKey(0);
}

void calc_camera_table_yz(const sensor_msgs::ImageConstPtr &msg) {
    cv_bridge::CvImagePtr imagePtr;
    try {
        imagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
        ROS_ERROR_STREAM("error info" << e.what());
        return;
    }

    //cv::imshow("image",imagePtr->image);
    imageProcess(imagePtr->image);
}

union DepthValue { // 利用共用体进行数据的转换
    float val;
    unsigned char arrs[4];
};

void calc_camera_table_x(const sensor_msgs::ImageConstPtr &msg) {
    //msg->data; 数据都在msg->data
    //msg->step | full row length in bytes
    if (ux == -1 || uy == -1) {
        std::cout << "calc_camera_table_yz 还未执行完毕" << std::endl;
        return;
    }

    int len = msg->data.size() / (msg->width * msg->height);// msg->data中 len 个长度代表一个图像值
    int idx = uy * msg->step + ux * len;// ux,uy的深度值 在 msg->data 中对应的索引
    DepthValue depth{};
    for (int i = 0; i < len; ++i) {
        depth.arrs[i] = msg->data[idx + i];
    }

    //std::cout << "桌子中心在相机坐标系下的x坐标是 : " << depth.val << " (m) " << std::endl;
    camera_table_x = depth.val;
}


int main(int argc, char **argv) {

    // 因为在世界坐标系下, 相机被我们固定到 (-0.55,0,1.0)位置,姿态是(0 pi/2 0) 所以外参矩阵(world -> camera)如下:
    //  cos90  0 sin90 -0.55
    //  0      1   0   0
    //  -sin90 0 cos90 1
    //  0      0   0   1
    cv::Mat ex_mat = cv::Mat::zeros(4, 4, CV_32F);//cv_32f float cv_64f double
    ex_mat.at<float>(0, 0) = cos(90 * M_PI / 180);
    ex_mat.at<float>(0, 2) = sin(90 * M_PI / 180);
    ex_mat.at<float>(1, 1) = 1;
    ex_mat.at<float>(2, 0) = -sin(90 * M_PI / 180);
    ex_mat.at<float>(2, 2) = cos(90 * M_PI / 180);
    ex_mat.at<float>(3, 3) = 1;

    ex_mat.at<float>(0, 3) = -0.55;
    ex_mat.at<float>(2, 3) = 1;

    std::string nodeName = "table_center";
    ros::init(argc, argv, nodeName, ros::init_options::AnonymousName);
    ros::NodeHandle node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    // 订阅ros 中的 /camera/color/image_raw  topic,利用它 算出桌子中心点在相机坐标系下的yz 坐标
    image_transport::ImageTransport it(node);
    const image_transport::Subscriber &subscriber = it.subscribe("/camera/color/image_raw", 1, calc_camera_table_yz);

    // 订阅ros 中的 /camera/depth/image_raw  topic,利用它 算出桌子中心点在相机坐标系下的x 坐标(因为Kinect是x朝向)
    const image_transport::Subscriber &subscriber2 = it.subscribe("/camera/depth/image_raw", 1, calc_camera_table_x);

    cv::Mat camera_pos = cv::Mat::zeros(4, 1, CV_32F);
    // 每隔1s 打印一次  相机坐标系下 table的坐标
    while (ros::ok()) {
        sleep(1);
        std::cout << "桌子中心在相机坐标系下的坐标(xyz)是 : " << camera_table_x << " " << camera_table_y << " " << camera_table_z
                  << std::endl;;

        camera_pos.at<float>(0, 0) = camera_table_x;
        camera_pos.at<float>(1, 0) = camera_table_y;
        camera_pos.at<float>(2, 0) = camera_table_z;
        camera_pos.at<float>(3, 0) = 1;
        cv::Mat world_pos = ex_mat * camera_pos;
        std::cout << "桌子中心在世界坐标系下的坐标(xyz)是 : "
                  << world_pos.at<float>(0, 0) << " "
                  << world_pos.at<float>(1, 0) << " "
                  << world_pos.at<float>(2, 0) << " "
                  << std::endl;;
    }


    return 0;
}
