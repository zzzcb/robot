//
// Created by zcb on 5/30/21.
//

#include <iostream>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/kdtree.h>


#include <cstdlib>
#include <ctime>


float random_float() {  // (0,1024) 小数
    return 1024.0f * rand() * 1.0 / RAND_MAX;  // 此时不会溢出
}

int main() {
    srand(time(NULL));

    // 1 准备点云
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());

    // cloud 基本配置
    cloud->width = 1000;
    cloud->height = 1;
    cloud->is_dense = false;
    cloud->points.resize(cloud->height * cloud->width);

    // 随机生成1000个 点
    for (int i = 0; i < 1000; ++i) {
        cloud->points[i].x = random_float();
        cloud->points[i].y = random_float();
        cloud->points[i].z = random_float();
    }
    // 保存 点云
    pcl::io::savePCDFileBinaryCompressed("./test.pcd", *cloud);

    // 2 构建kd tree
    pcl::search::KdTree<pcl::PointXYZ> kdtree;
    kdtree.setInputCloud(cloud); //对 cloud 进行 kd tree 分割

    // 3 初始化一个随机点 (以此点 为基础 搜索离该点最近的 10个点)
    pcl::PointXYZ point;
    point.x = random_float();
    point.y = random_float();
    point.z = random_float();
    std::cout << "选取的初始点是 : " << point << std::endl;


    // 搜索方式1: nearest k neighbor search ,最近的k个
    int K = 10; // 最近的10 个邻居
    std::vector<int> pointIdxs1; // 输出参数
    std::vector<float> pointDistances1; // 输出参数
    if (kdtree.nearestKSearch(point, K, pointIdxs1, pointDistances1)) {
        // 有邻居
        for (int i = 0; i < pointIdxs1.size(); ++i) {
            int idx = pointIdxs1[i]; // 索引
            // 打印 此点的数值 和 距离的平方
            std::cout << "  " << cloud->points[idx].x
                      << "  " << cloud->points[idx].y
                      << "  " << cloud->points[idx].z
                      << " (距离平方: " << pointDistances1[i] << ")" << std::endl;
        }
    }



    // 搜索方式2: neighbors within radius search ,指定半径内的点
    int radius = 256.0f;
    std::vector<int> pointIdxs2; // 输出参数
    std::vector<float> pointDistances2; // 输出参数

    if (kdtree.radiusSearch(point, radius, pointIdxs2, pointDistances2)) {
        std::cout << "搜索半径是 " << radius<<std::endl;
        // 有邻居
        for (int i = 0; i < pointIdxs2.size(); ++i) {
            int idx = pointIdxs2[i]; // 索引
            // 打印 此点的数值 和 距离的平方
            std::cout << "  " << cloud->points[idx].x
                      << "  " << cloud->points[idx].y
                      << "  " << cloud->points[idx].z
                      << " (距离平方: " << pointDistances2[i] << ")" << std::endl;
        }
    }


    return 0;
}

