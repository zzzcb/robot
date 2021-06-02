//
// Created by zcb on 6/1/21.
//
/*
 * 从深度图 提取边界
 */

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/range_image/range_image.h> // 深度图 基本
#include <pcl/features/range_image_border_extractor.h> // 深度图 提取3个边缘
#include <pcl/visualization/range_image_visualizer.h> // 深度图 二维展示
#include <pcl/console/parse.h> // 命令行解析工具

using namespace std;

float angular_resolution = 0.5f;
pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::LASER_FRAME;// Camera_frame 也可以
bool setUnseenToMaxRange = false; // 是否设置 没扫描到的 深度为 最大的深度

// help
void printUsage(const char *progName) {
    std::cout << "\n\nUsage: " << progName << " [options] <scene.pcd>\n\n"
              << "Options:\n"
              << "-------------------------------------------\n"
              << "-r <float>   angular resolution in degrees (default " << angular_resolution << ")\n"
              << "-c <int>     coordinate frame (default " << (int) coordinate_frame << ")\n"
              << "-m           Treat all unseen points to max range\n"
              << "-h           this help\n"
              << "\n\n";
}

int main(int argc, char **argv) {
    //1. 命令行解析器
    if (pcl::console::find_argument(argc, argv, "-h") >= 0) { // 含有-h
        printUsage(argv[0]);
        return 0;
    }
    if (pcl::console::find_argument(argc, argv, "-m") >= 0) {
        setUnseenToMaxRange = true;
        cout << "Setting unseen values in range image to maximum range readings.\n";
    }

    int tmp_coordinate_frame; // 输出参数
    if (pcl::console::parse(argc, argv, "-c", tmp_coordinate_frame) >= 0) {//使用 CameraFrame
        coordinate_frame = pcl::RangeImage::CoordinateFrame(tmp_coordinate_frame);
        cout << "Using coordinate frame " << (int) coordinate_frame << ".\n";
    }
    if (pcl::console::parse(argc, argv, "-r", angular_resolution) >= 0) {
        cout << "Setting angular resolution to " << angular_resolution << "deg.\n";
    }
    angular_resolution = pcl::deg2rad(angular_resolution); // 角度 to  弧度

    //2. 如果有 pcd文件就读取,不然自动生成一个点云
    Eigen::Affine3f sensor_pose(Eigen::Affine3f::Identity());// 默认 点云视角

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    vector<int> files = pcl::console::parse_file_extension_argument(argc, argv, "pcd");
    //files[0] 存放的是 pcd 文件在 argv 中的 索引
    if (!files.empty()) { // 有pcd 文件
        string file_path = argv[files[0]];
        //cout << file_path << endl;
        if (pcl::io::loadPCDFile(file_path, *cloud) == -1) {
            //加载失败
            PCL_ERROR("加载pcd文件失败,[ %s ]", file_path.c_str());
            return -1;
        }
        sensor_pose = // 传感器的 位姿
                // 先旋转 后平移 左乘
                Eigen::Affine3f(Eigen::Translation3f(cloud->sensor_origin_[0], cloud->sensor_origin_[1],
                                                     cloud->sensor_origin_[2])) * // 位置
                Eigen::Affine3f(cloud->sensor_orientation_);  // 姿态
    } else { // 无 pcd 文件
        //生成一个点云
        for (float y = -0.5; y <= 0.5; y += 0.01) {
            for (float z = -0.5; z <= 0.5; z += 0.01) {
                cloud->points.push_back(pcl::PointXYZ(2.0 - y, y, z));
            }
        }
        cloud->width = cloud->points.size();
        cloud->height = 1;
    }

    //3 点云图 to 深度图
    pcl::RangeImage::Ptr range_image_ptr(new pcl::RangeImage);
    float max_angle_width = 360.0 * M_PI / 180.0f;
    float max_angle_height = 180 * M_PI / 180.0f;
    range_image_ptr->createFromPointCloud(*cloud, angular_resolution, max_angle_width, max_angle_height, sensor_pose,
                                          coordinate_frame);

    //4 显示 原始点云 和 深度图
    pcl::visualization::PCLVisualizer pclVisualizer("visualizer");
    pclVisualizer.setBackgroundColor(0.1, 0.5, 0.1);
    pclVisualizer.addCoordinateSystem(1.0); // 坐标轴长 1m

    // 原始点云
    pclVisualizer.addPointCloud(cloud, "cloud"); // 原始点云

    // 深度图
    /*
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> color(range_image_ptr, 255, 0, 0);// 红色
    pclVisualizer.addPointCloud<pcl::PointWithRange>(range_image_ptr, color,
                                                     "depth_image");
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 4,
                                                   "depth_image");
    */


    //5 提取边缘信息
    if (setUnseenToMaxRange) {
        range_image_ptr->setUnseenToMaxRange();
    }
    pcl::RangeImageBorderExtractor borderExtractor(&(*range_image_ptr));

    pcl::PointCloud<pcl::BorderDescription> border_descs;// 传出 参数,容器
    borderExtractor.compute(border_descs);


    //6 从 range_image中 分出3种边缘 对象,背景,面纱
    pcl::PointCloud<pcl::PointWithRange>::Ptr
            obstacle_points_ptr(new pcl::PointCloud<pcl::PointWithRange>),
            veil_points_ptr(new pcl::PointCloud<pcl::PointWithRange>),
            shadow_points_ptr(new pcl::PointCloud<pcl::PointWithRange>);
    for (int i = 0; i < range_image_ptr->height; ++i) {
        for (int j = 0; j < range_image_ptr->width; ++j) {
            int idx = i * range_image_ptr->width + j;
            pcl::BorderTraits bitset = border_descs[idx].traits;  // 该点的描述
            if (bitset[pcl::BORDER_TRAIT__OBSTACLE_BORDER]) {
                // 目标边缘点
                obstacle_points_ptr->points.push_back(range_image_ptr->points[idx]);
            }
            if (bitset[pcl::BORDER_TRAIT__SHADOW_BORDER]) {
                // 阴影边缘点
                shadow_points_ptr->points.push_back(range_image_ptr->points[idx]);
            }
            if (bitset[pcl::BORDER_TRAIT__VEIL_POINT]) {
                // 面纱边缘点
                veil_points_ptr->points.push_back(range_image_ptr->points[idx]);
            }
        }
    }

    // 7 展示 3种 边缘
    // obstale border
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> red_color(obstacle_points_ptr, 255, 0,
                                                                                    0);// 红色
    pclVisualizer.addPointCloud<pcl::PointWithRange>(obstacle_points_ptr, red_color,
                                                     "obstacle_border");
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,
                                                   "obstacle_border");
    // shadow border
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> green_color(obstacle_points_ptr, 0, 255,
                                                                                      0);// 绿色
    pclVisualizer.addPointCloud<pcl::PointWithRange>(shadow_points_ptr, green_color,
                                                     "shadow_border");
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 4,
                                                   "shadow_border");

    // veil points
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> blue_color(obstacle_points_ptr, 0, 0,
                                                                                     255);// 蓝色
    pclVisualizer.addPointCloud<pcl::PointWithRange>(veil_points_ptr, blue_color,
                                                     "veil_border");
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 6,
                                                   "veil_border");

    // 8 展示 二维深度图
    pcl::visualization::RangeImageVisualizer *range_image_visualizer = pcl::visualization::RangeImageVisualizer::getRangeImageBordersWidget(
            *range_image_ptr, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), false,
            border_descs);

    while (!pclVisualizer.wasStopped()) {
        pclVisualizer.spinOnce();
        range_image_visualizer->spinOnce();

        pcl_sleep(0.01);
    }

    return 0;
}
