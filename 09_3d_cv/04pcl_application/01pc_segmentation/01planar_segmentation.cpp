//
// Created by zcb on 6/13/21.
//
/*
 * 点云分割-- 平面模型分割
 * http://robot.czxy.com/docs/pcl/chapter04/segmentation/#_2
 */

#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/visualization/pcl_visualizer.h>

#include <cstdlib>
#include <ctime>

using namespace std;

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}

int main(int argc, char **argv) {
    srand(time(NULL));

    PointCloudT::Ptr cloud(new PointCloudT);
    //1 随机生成15 个点(-1,1) ,xy 随机 z=1.0 | 其中索引为 0,3,6 的点的z 随机修改作为离群值
    cloud->width = 15;
    cloud->height = 1;
    cloud->resize(cloud->width * cloud->height);
    for (int i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = random_float();
        cloud->points[i].y = random_float();
        cloud->points[i].z = 1.0;
        if (i == 0 || i == 3 || i == 6)
            cloud->points[i].z += random_float();
    }


    //2 分割器
    pcl::SACSegmentation<PointT> seg; // ransac
    seg.setOptimizeCoefficients(true); // 优化模型系数
    seg.setModelType(pcl::SACMODEL_PLANE); //平面
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.01);// 设置阈值为 0.01m
    seg.setInputCloud(cloud);

    //执行分割
    //inliers 传出参数,符合模型的点
    //coefficients 传出参数,模型的系数
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    seg.segment(*inliers, *coefficients);

    if (inliers->indices.size() == 0) {
        PCL_ERROR ("Could not estimate a planar model for the given dataset.");
        return (-1);
    } else {
        //此段代码用来打印出估算的平面模型的参数（以 ax+by+cz+d=0 形式）,详见RANSAC采样一致性算法的SACMODEL_PLANE平面模型
        cout << "Model coefficients: " << coefficients->values[0] << " "
             << coefficients->values[1] << " "
             << coefficients->values[2] << " "
             << coefficients->values[3] << std::endl;
    }

    //3 得出符合模型的点云
    PointCloudT::Ptr cloud_model(new PointCloudT);
    pcl::copyPointCloud(*cloud, *inliers, *cloud_model);

    //4 可视化展示
    pcl::visualization::PCLVisualizer visualizer;
    visualizer.addPointCloud(cloud, "cloud");

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> red_color(cloud_model, 255, 0, 0);// 红色
    visualizer.addPointCloud(cloud_model, red_color, "cloud_model"); // 符合模型的点云
    visualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud_model");

    visualizer.addCoordinateSystem(1.0);

    while (!visualizer.wasStopped()) {
        visualizer.spinOnce(100);
    }


    return 0;
}
