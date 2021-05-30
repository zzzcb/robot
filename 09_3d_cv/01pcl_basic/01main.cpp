//
// Created by zcb on 5/29/21.
//

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

int main(int argc, char **argv) {

    // 创建一个空的点云容器, 并用cloud 智能指针 指向它
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    // 加载pcd文件 到 cloud
    pcl::io::loadPCDFile("../data/pcl_logo.pcd",*cloud);

    // 显示点云
    pcl::visualization::CloudViewer viewer("Cloud Viewer by zcb");
    viewer.showCloud(cloud);

    // 循环判断是否退出
    while (!viewer.wasStopped()) {
        // 你可以在这里对点云做很多处理
    }

    return 0;
}







