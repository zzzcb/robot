//
// Created by zcb on 5/30/21.
//

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

#include <cstdlib>
#include <ctime>

/*
 * 随机生成5 个点,将其保存到文件 【序列化serialize】
 */

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}


int main() {

    srand(time(NULL));
    pcl::PointCloud<pcl::PointXYZ> cloud;

    // 设置点云基础属性
    cloud.width = 5;
    cloud.height = 1;
    cloud.is_dense = false;// 是否是 密集点
    cloud.points.resize(cloud.width * cloud.height);

    // 随机生成 5 个点
    for (int i = 0; i < cloud.size(); ++i) {
        cloud.points[i].x = random_float();
        cloud.points[i].y = random_float();
        cloud.points[i].z = random_float();
    }

    // 序列化到本地 dump,save
//    pcl::io::savePCDFileASCII("./test_pcd_ascii.pcd", cloud); // ascii 易于人观看 一般不使用
    pcl::io::savePCDFileBinaryCompressed("./test_pcd_bi_compress.pcd", cloud);

    return 0;
}

