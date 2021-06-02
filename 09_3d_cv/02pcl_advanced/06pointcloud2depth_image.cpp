//
// Created by zcb on 6/1/21.
//
/*
 * 点云 转化为 深度图 depth image 也叫range image
 */

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/range_image/range_image.h>

using namespace std;

int main(int argc, char **argv) {

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    //1. 生成一个点云
    for (float y = -0.5; y <= 0.5; y += 0.01) {
        for (float z = -0.5; z <= 0.5; z += 0.01) {
            cloud->points.push_back(pcl::PointXYZ(2.0 - y, y, z));
        }
    }
    cloud->width = cloud->points.size();
    cloud->height = 1;

    // 展示点云
    pcl::visualization::PCLVisualizer pclVisualizer("visualizer");
    pclVisualizer.setBackgroundColor(0.1, 0.5, 0.1);
//    pclVisualizer.addCoordinateSystem(1.0); // 坐标轴长 1m
    pclVisualizer.addCoordinateSystem(2.0);

    pclVisualizer.addPointCloud(cloud, "cloud");

    //2. 点云 to 深度图
    pcl::RangeImage::Ptr range_image_ptr(new pcl::RangeImage);

    float angular_resolution = M_PI / 180.0f; // 采集时的 步长
    float max_angle_width = 360.0* M_PI / 180.0f;// 水平逆时针最大角度   // 初始时 摄像机的朝向是 X 反向
    float max_angle_height = 180 * M_PI / 180.0f;// 垂直上下转动 的范围
    Eigen::Affine3f sensor_pose = (Eigen::Affine3f) Eigen::Translation3f(0, 0, 0); // 采集的位置 (相机的位置)
    pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME; // 参考坐标系

    range_image_ptr->createFromPointCloud(*cloud, angular_resolution, max_angle_width, max_angle_height, sensor_pose,
                                        coordinate_frame); // 创建之后的 数据会存储回本体 range_img_ptr

    //3 可视化展示 深度图
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> color(range_image_ptr, 255, 0, 0);// 红色
    pclVisualizer.addPointCloud<pcl::PointWithRange>(range_image_ptr, color,
                                                     "range_image"); //================重点=================
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 4,
                                                   "range_image"); // 设置 size 大小

    while (!pclVisualizer.wasStopped()) {
        pclVisualizer.spinOnce();
        pcl_sleep(0.01);
    }

    return 0;
}




