//
// Created by zcb on 6/14/21.
//
/*
 * 曲面重建
 *    插值法(原始点中插入新的点)
 *    逼近法(用新的点逼近原始点) 本程序使用此方法
 *    http://robot.czxy.com/docs/pcl/chapter04/resampling/
 */
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h> // move least square 移动最小二乘法
#include <pcl/visualization/cloud_viewer.h>

using namespace std;

int main(int argc, char **argv) {
    //1 加载点云
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::io::loadPCDFile("../data/target.pcd", *cloud);

    //2 移动最小二乘
    pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
    mls.setComputeNormals(true);
    mls.setInputCloud(cloud);
    mls.setPolynomialOrder(2); // MLS 拟合的阶数

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointNormal> mls_points;
    mls.setSearchMethod(tree);
    mls.setSearchRadius(0.03);
    //3 曲面重建
    mls.process(mls_points); // 重建 将结果输出到 mls_points

    //4 可视化展示 原始点云
    pcl::visualization::CloudViewer viewer("Cloud Viewer");;
    viewer.showCloud(cloud);
    while (!viewer.wasStopped()) {
    }
    //4 保存 重建后的点云到文件
    pcl::io::savePCDFile("../data/target-mls.pcd", mls_points);


    return 0;
}


