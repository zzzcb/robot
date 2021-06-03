//
// Created by zcb on 6/3/21.
//
#include <iostream>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/features/normal_3d.h> // 法向量估计

#include <pcl/filters/voxel_grid.h> // 降采样

using namespace std;

/*
 * 估算表面法线的 三个函数
 * setInputCloud    [必有]
 * setIndices       [可选]
 * setSearchSurface [可选]
 */
/*
 * 这里使用  setInputCloud 和 setSurface[把降采样的点作为inputCloud,然后将原始点云作为Surface进行计算]
 */
int main(int argc, char **argv) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("../data/target.pcd", *cloud);

    //1. ======================进行降采样=========================
    // 长宽高 分别为 1cm 的过滤器
    pcl::VoxelGrid<pcl::PointXYZ> voxel;
    voxel.setInputCloud(cloud);
    float leafSzie = 0.04;
    voxel.setLeafSize(leafSzie, leafSzie, leafSzie);
    voxel.filter(*cloud_filtered); // 输出参数

    //2. 创建法线估算器
    // 输出参数  用于存放计算好的 法线结果
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    // 输入,输出 类型
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
    normalEstimation.setInputCloud(cloud_filtered);

    //3 设置 Surface
    normalEstimation.setSearchSurface(cloud);

    normalEstimation.setRadiusSearch(0.03);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kd_tree(new pcl::search::KdTree<pcl::PointXYZ>);
    normalEstimation.setSearchMethod(kd_tree);

    // 开始执行
    normalEstimation.compute(*normals);

    //4 可视化展示
    pcl::visualization::PCLVisualizer pclVisualizer("pcl viewer");
    pclVisualizer.addCoordinateSystem(0.05); // 每个 坐标系长 0.05m
    pclVisualizer.setBackgroundColor(0, 0, 0);
    pclVisualizer.addPointCloud<pcl::PointXYZ>(cloud, "cloud");

    // cloud_filtered 的数量 一定要等于normals // 每个点都有它自己的法向量
    int level = 3; // 显示的时候,每 level 个点展示一个法向量
    double scale = 0.01; // 显示的时候, 将法向量的大小进行缩放
    pclVisualizer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud_filtered, normals, level, scale, "normals");

    while (!pclVisualizer.wasStopped()) {
        pclVisualizer.spinOnce();

        pcl_sleep(0.01);
    }

    return 0;
}

