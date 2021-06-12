//
// Created by zcb on 6/12/21.
//

/*
 * ndt 点云配准
 * http://robot.czxy.com/docs/pcl/chapter03/registration/
 */

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/registration/ndt.h>  // ndt 点云配准
#include <pcl/filters/approximate_voxel_grid.h> // 滤波 ,降采样

using namespace std;
//using namespace std::chrono_literals;


int main(int argc, char **argv) {

    //1 target_cloud 加载room_scan1
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("../data/room_scan1.pcd", *target_cloud);

    //2 input_cloud 加载room_scan2
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("../data/room_scan2.pcd", *input_cloud);

    // 我们需要做的是 求出 input -> target 的变换矩阵

    //3 对 input_cloud 进行降采样,目标点云不用降采样
    pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
    approximate_voxel_filter.setLeafSize(0.2, 0.2, 0.2);
    approximate_voxel_filter.setInputCloud(input_cloud);
    approximate_voxel_filter.filter(*filtered_cloud);

    //4 ndt对象
    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;
    ndt.setTransformationEpsilon(0.01); // 为终止条件设置最小转换差异
    ndt.setStepSize(0.1);   // 为More-Thuente线搜索设置最大步长
    ndt.setResolution(1.0); // 设置NDT网格结构的分辨率 VoxelGridCovariance
    ndt.setMaximumIterations(35);//设置匹配迭代的最大次数

    ndt.setInputSource(filtered_cloud);// 设置过滤后的输入源点云
    ndt.setInputTarget(target_cloud);// 设置目标点云

    //5 设置使用机器人测距法得到的粗略初始变换矩阵
    Eigen::AngleAxisf init_rotation(0.6931, Eigen::Vector3f::UnitZ()); //大概相差 40度
    Eigen::Translation3f init_translation(1.79387, 0, 0); // 大概相差1.79m
    Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();

    //6 计算所需的刚体变换,以使输入云与目标云对齐
    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    ndt.align(*output_cloud, init_guess); // 配准
    cout << "output size " << output_cloud->points.size() << endl;

    cout << "是否收敛 " << ndt.hasConverged() << endl;
    cout << "配准分数: " << ndt.getFitnessScore() << endl;
    cout << "input 到 target 的变换矩阵: \n" << ndt.getFinalTransformation() << endl;

    //7 使用找到的变换矩阵,来对未过滤的输入云进行变换
    pcl::transformPointCloud(*input_cloud, *output_cloud, ndt.getFinalTransformation());
    cout << "output size " << output_cloud->points.size() << endl;

    //8 保存变换后的输入点云
    pcl::io::savePCDFileASCII("../data/room_scan2_transformed.pcd", *output_cloud);

    //9 可视化 展示target(red 不动) 和 input(green 配准后的green)
    pcl::visualization::PCLVisualizer::Ptr viewer_final(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer_final->setBackgroundColor(0, 0, 0);

    // Coloring and visualizing target cloud (red).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> target_color(target_cloud, 255, 0, 0);
    viewer_final->addPointCloud<pcl::PointXYZ>(target_cloud, target_color, "target cloud");
    viewer_final->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "target cloud");

    // Coloring and visualizing transformed input cloud (green).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> output_color(output_cloud, 0, 255, 0);
    viewer_final->addPointCloud<pcl::PointXYZ>(output_cloud, output_color, "output cloud");
    viewer_final->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "output cloud");

    viewer_final->addCoordinateSystem(1.0, "global");
    //viewer_final->initCameraParameters();

    while (!viewer_final->wasStopped()) {
        viewer_final->spinOnce(100);
    }

    return 0;
}
