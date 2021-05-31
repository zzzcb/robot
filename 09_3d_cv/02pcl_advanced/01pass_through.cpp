//
// Created by zcb on 5/30/21.
//

/*
 * 直通滤波 pass_through, 裁剪,满足条件的才会留下
 */

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/filters/passthrough.h>

#include <cstdlib>
#include <ctime>

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}


int main() {
    srand(time(NULL));

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    //1. 准备5 个点
    // 基础配置
    cloud->width = 5;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    // 随机生成5 个点
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = random_float();
        cloud->points[i].y = random_float();
        cloud->points[i].z = random_float();
    }

    // 2 构建 直通滤波器 条件是 z (0,1)
    pcl::PassThrough<pcl::PointXYZ> passThrough;
    passThrough.setInputCloud(cloud);
    passThrough.setFilterFieldName("z");
    passThrough.setFilterLimits(0.0, 1.0);
    //passThrough.setNegative(true);// 取反,此时保留的是 limit以外的数据

    std::cout << "-------------before filter --------------" << std::endl;
    for (int i = 0; i < cloud->size(); ++i) {
        std::cout << cloud->points[i].x << " "
                  << cloud->points[i].y << " "
                  << cloud->points[i].z << std::endl;
    }
    // 3 进行过滤
    passThrough.filter(*cloud_filtered); // cloud_filtered 是输出参数
    std::cout << "-------------after filter --------------" << std::endl;

    for (int i = 0; i < cloud_filtered->size(); ++i) {
        std::cout << cloud_filtered->points[i].x << " "
                  << cloud_filtered->points[i].y << " "
                  << cloud_filtered->points[i].z << std::endl;
    }


    return 0;
}

