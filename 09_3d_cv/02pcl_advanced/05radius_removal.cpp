//
// Created by zcb on 5/31/21.
//

/*
 * 离群点的移除: Radius Outlier Removal 半径离群值滤波, 更适合实时的数据移除.
 * 精度低,速度快
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/radius_outlier_removal.h>


#include <cstdlib>
#include <ctime>

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}

int main() {
    srand(time(NULL));

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    //1. 准备 点云
    cloud->width = 100;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    // 随机生成100 个点
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = random_float();
        cloud->points[i].y = random_float();
        cloud->points[i].z = random_float();
    }


    //2 创建 半径离群值滤波
    pcl::RadiusOutlierRemoval<pcl::PointXYZ> ror;
    ror.setInputCloud(cloud);
    ror.setRadiusSearch(0.4); // 0.4 m
    ror.setMinNeighborsInRadius(2); // 最少两个点

    std::cout << "过滤前点云的数量: " << cloud->width * cloud->height
              << " 点云的字段列表: " << pcl::getFieldsList(*cloud)
              << std::endl;

    //3 进行过滤
    ror.filter(*cloud_filtered);

    std::cout << "过滤后点云的数量: " << cloud_filtered->width * cloud_filtered->height
              << std::endl;

    //4 保存点云到文件
    pcl::PCDWriter pcdWriter;
    pcdWriter.writeBinaryCompressed("../data/test.pcd", *cloud_filtered);

}

