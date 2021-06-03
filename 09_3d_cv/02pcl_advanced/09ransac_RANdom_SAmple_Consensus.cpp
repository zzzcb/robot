//
// Created by zcb on 6/2/21.
//

/*
 * RANSAC: RANdom SAmple Consensus 随机抽样一致性 算法
 *
 * 使用方式: 【s:sphere f:fitting】
 *  ./output        // 显示点云
 *  ./output -f     // 显示拟合出的 平面
 *
 *  ./output -s     // 显示球体
 *  ./output -sf    // 显示拟合出的 球体
 */
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/sample_consensus/sac_model_plane.h> // 平面模型
#include <pcl/sample_consensus/sac_model_sphere.h> // 球模型

#include <pcl/sample_consensus/ransac.h> //ransac 基础

#include <pcl/console/parse.h> // 命令行解析工具

#include <cstdlib> // 随机数 srand()
#include <ctime> // time()

using namespace std;

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}

int main(int argc, char **argv) {
    srand(time(NULL));

    //1 生成 500个 [-1,1] 的平面 和 球体的 随机点
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fit(new pcl::PointCloud<pcl::PointXYZ>);

    // 点云基本设置
    cloud->width = 500;
    cloud->height = 1;
    cloud->is_dense = false;
    cloud->resize(cloud->width * cloud->height);

    for (int i = 0; i < 500; ++i) {
        float x = random_float();
        float y = random_float();
        cloud->points[i].x = x;
        cloud->points[i].y = y;
        if (pcl::console::find_argument(argc, argv, "-s") >= 0 || pcl::console::find_argument(argc, argv, "-sf") >= 0) {
            // 生成包含 球体的随机点 1/5 随机点  4/5 球点
            if (i % 5 == 0)
                cloud->points[i].z = random_float();  // 1/5
            else if (i % 2 == 0)
                cloud->points[i].z = sqrt(1 - pow(x, 2) - pow(y, 2)); // 2/5
            else
                cloud->points[i].z = -sqrt(1 - pow(x, 2) - pow(y, 2)); // 2/5
        } else {
            // 生成包含 平面的随机点 1/2 随机点 1/2 平面点
            if (i % 2 == 0)
                cloud->points[i].z = x + y;
            else
                cloud->points[i].z = random_float();
        }
    }

    // 可视化展示点云
    pcl::visualization::PCLVisualizer pclVisualizer("visualizer");
    pclVisualizer.addCoordinateSystem(1.0); // 坐标轴长 1m
    pclVisualizer.addPointCloud(cloud, "cloud");

    //2.创建 平面模型 和 球体模型
    pcl::SampleConsensusModelPlane<pcl::PointXYZ>::Ptr model_plane(
            new pcl::SampleConsensusModelPlane<pcl::PointXYZ>(cloud));
    pcl::SampleConsensusModelSphere<pcl::PointXYZ>::Ptr model_sphere(
            new pcl::SampleConsensusModelSphere<pcl::PointXYZ>(cloud));

    vector<int> in_idxs; // 模型上的点的 索引

    //3. 设置ransac 参数
    if (pcl::console::find_argument(argc, argv, "-f") >= 0) {
        // 平面拟合
        pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model_plane);
        ransac.setDistanceThreshold(0.01);// 模型的最大阈值 0.01m
        ransac.computeModel();
        ransac.getInliers(in_idxs);
    } else if (pcl::console::find_argument(argc, argv, "-sf") >= 0) {
        // 球体拟合
        pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model_sphere);
        ransac.setDistanceThreshold(0.01);// 模型的最大阈值 0.01m
        ransac.computeModel();
        ransac.getInliers(in_idxs);
    }

    //4 从原有点云中 提取出 拟合出的点
    pcl::copyPointCloud(*cloud, in_idxs, *cloud_fit);
    if (in_idxs.size() > 0) {
        // 展示拟合出的 点云
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_red(cloud_fit, 255, 0, 0);// 红色
        pclVisualizer.addPointCloud(cloud_fit, color_red, "cloud_fit");
        pclVisualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,
                                                       "cloud_fit");
    }


    while (!pclVisualizer.wasStopped()) {
        pclVisualizer.spinOnce();

        pcl_sleep(0.01);
    }


    return 0;
}
