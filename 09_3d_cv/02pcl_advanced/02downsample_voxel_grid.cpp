//
// Created by zcb on 5/30/21.
//


/*
 * 对 点云进行降采样
 * 将 降采样 后的点云 保存到文件
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>

int main() {
    //  pcl::PCLPointCloud2 不需要指定 数据类型,比 pcl::PointCloud 好
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2()); // 降采样后的点云

    //1. 从文件中 读取点云数据
    pcl::PCDReader pcdReader;
    pcdReader.read("../data/table_scene_lms400.pcd", *cloud);

    std::cout << "过滤前点云的数量: " << cloud->width * cloud->height
              << " 点云的字段列表: " << pcl::getFieldsList(*cloud)
              << std::endl;

    // ======================进行降采样=========================
    // 长宽高 分别为 1cm 的过滤器
    // 2 构建 滤波器
    pcl::VoxelGrid<pcl::PCLPointCloud2> voxel;
    voxel.setInputCloud(cloud);
    float leafSzie = 0.01;
    voxel.setLeafSize(leafSzie, leafSzie, leafSzie);

    // 3 进行 降采样
    voxel.filter(*cloud_filtered); // 输出参数

    std::cout << "过滤后点云的数量: " << cloud_filtered->width * cloud_filtered->height
              << std::endl;

    // 4 写出到 文件
    pcl::PCDWriter pcdWriter;
    pcdWriter.writeBinaryCompressed("../data/table_scene_lms400_downsampled.pcd", *cloud_filtered);

    return 0;
}

