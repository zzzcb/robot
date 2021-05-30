//
// Created by zcb on 5/30/21.
//
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>


int main() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_bunny(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("../data/bunny.pcd", *cloud_bunny);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_milk(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile("../data/milk_color.pcd", *cloud_milk);

    pcl::visualization::PCLVisualizer visualizer("PCL Visualizer by zcb");

    visualizer.setBackgroundColor(0.5, 0.5, 0.5); // 颜色值 0 - 1
    visualizer.addCoordinateSystem(1.0); //添加一个缩放 1倍 的 坐标轴

    // 添加点云
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud_bunny, 0, 255, 0);
    visualizer.addPointCloud<pcl::PointXYZ>(cloud_bunny, single_color,"cloud_bunny");
    visualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,2,"cloud_bunny"); // 设置点的大小

    // 再添加一个点云 ,本身有颜色 不需要加颜色
    visualizer.addPointCloud<pcl::PointXYZRGB>(cloud_milk,"cloud_milk");
    visualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,3,"cloud_milk");

    while(!visualizer.wasStopped()){
        visualizer.spinOnce();
    }


    return 0;
}

