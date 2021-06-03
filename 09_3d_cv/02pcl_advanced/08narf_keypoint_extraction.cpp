//
// Created by zcb on 6/2/21.
//

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/range_image/range_image.h> // 深度图
#include <pcl/features/range_image_border_extractor.h>//从 深度图 分离边缘
#include <pcl/keypoints/narf_keypoint.h> // narf 关键点提取
#include <pcl/console/parse.h> // 命令行 解析工具

#include <pcl/visualization/pcl_visualizer.h> // 显示点云
#include <pcl/visualization/range_image_visualizer.h> // 显示二维 深度图

using namespace std;

float angular_resolution = 0.5f;
float support_size = 0.2f; // 关键点 提取时 的范围 0.2m, 在决定A点是否是关键点时,需要从A点周围0.2m 的范围来判断是否是关键点
pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
bool setUnseenToMaxRange = false;

void printUsage(const char *progName) {
    std::cout << "\n\nUsage: " << progName << " [options] <scene.pcd>\n\n"
              << "Options:\n"
              << "-------------------------------------------\n"
              << "-r <float>   angular resolution in degrees (default " << angular_resolution << ")\n"
              << "-c <int>     coordinate frame (default " << (int) coordinate_frame << ")\n"
              << "-m           Treat all unseen points as maximum range readings\n"
              << "-s <float>   support size for the interest points (diameter of the used sphere - "
              << "default " << support_size << ")\n"
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
    if (pcl::console::parse(argc, argv, "-s", support_size) >= 0) {
        cout << "Setting support size to " << support_size << ".\n";
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
    pclVisualizer.setBackgroundColor(1, 1, 1);
    pclVisualizer.addCoordinateSystem(1.0); // 坐标轴长 1m

    // 原始点云
    //pclVisualizer.addPointCloud(cloud, "cloud"); // 原始点云

    // 深度图
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> color(range_image_ptr, 255, 0, 0);// 红色
    pclVisualizer.addPointCloud<pcl::PointWithRange>(range_image_ptr, color,
                                                     "depth_image");
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,
                                                   "depth_image");
    // 深度图 二维
    pcl::visualization::RangeImageVisualizer rangeImageVisualizer("2d range image");
    rangeImageVisualizer.showRangeImage(*range_image_ptr);


    //5 提取 narf 关键点
    pcl::RangeImageBorderExtractor rangeImageBorderExtractor;
    pcl::NarfKeypoint narfKeypointDectector(&rangeImageBorderExtractor);
    narfKeypointDectector.setRangeImage(&(*range_image_ptr));
    narfKeypointDectector.getParameters().support_size = support_size; // 设置 关键点提取时的范围

    pcl::PointCloud<int> keypoint_idxs; // 关键点的索引,是 range_image_ptr 中的索引
    narfKeypointDectector.compute(keypoint_idxs);

    PCL_INFO("发现了%d个关键点\n", keypoint_idxs.size());
    //6 将关键点从 深度图 中提取出来
    pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints_ptr(new pcl::PointCloud<pcl::PointXYZ>); // 容器
    keypoints_ptr->resize(keypoint_idxs.size());

    for (int i = 0; i < keypoint_idxs.size(); ++i) {
        int idx = keypoint_idxs.points[i]; // 关键点 在 range_image 中的索引
        pcl::PointWithRange range = range_image_ptr->points[idx];

        keypoints_ptr->points[i].x = range.x; // 将深度图中的 关键点的xyz 信息存储到 keypoints中
        keypoints_ptr->points[i].y = range.y;
        keypoints_ptr->points[i].z = range.z;
        // 上面三行 可以用下面一行代替
        // keypoints.points[i].getArray3fMap() = range.getArray3fMap();
    }

    //7 展示 找出来的 关键点
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> blue_color(keypoints_ptr, 0, 0, 255);// 蓝色
    pclVisualizer.addPointCloud<pcl::PointXYZ>(keypoints_ptr, blue_color,
                                                     "key_points");
    pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 8,
                                                   "key_points");

/*
 */

    while (!pclVisualizer.wasStopped()) {
        pclVisualizer.spinOnce();
        rangeImageVisualizer.spinOnce();

        pcl_sleep(0.01);
    }


    return 0;
}

