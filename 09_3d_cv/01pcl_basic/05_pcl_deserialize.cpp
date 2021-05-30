//
// Created by zcb on 5/30/21.
//

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

int main() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr bunny_cloud(new pcl::PointCloud<pcl::PointXYZ>());

    // 反序列化 就是  load
    if (pcl::io::loadPCDFile("../data/bunny.pcd", *bunny_cloud) == -1) {
        PCL_ERROR("couldn't open file bunny.pcd\n");
        return -1;
    }

    std::cout << "point cloud width:" << bunny_cloud->width << std::endl;
    std::cout << "point cloud height:" << bunny_cloud->height << std::endl;
    std::cout << "point cloud size:" << bunny_cloud->size() << std::endl;

    for (int i = 0; i < bunny_cloud->size(); ++i) {
        std::cout << "point cloud point:  x " << bunny_cloud->points[i].x
                  << " y " << bunny_cloud->points[i].y
                  << " z " << bunny_cloud->points[i].z
                  << std::endl;
    }

    return 0;
}








