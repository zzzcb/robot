//
// Created by zcb on 6/13/21.
//
/*
 * 点云分割-- 欧式聚类提取
 * http://robot.czxy.com/docs/pcl/chapter04/segmentation/#_10
 */
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/kdtree/kdtree.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl/visualization/pcl_visualizer.h>

using namespace std;

int main(int argc, char **argv) {

    // 读取点云
    pcl::PCDReader reader;
    pcl::PointCloud<pcl::PointXYZ>::Ptr
            cloud(new pcl::PointCloud<pcl::PointXYZ>),
            cloud_f(new pcl::PointCloud<pcl::PointXYZ>);
    reader.read("../data/tabletop.pcd", *cloud);
    cout << "PointCloud before filtering has: " << cloud->points.size() << " data points." << endl; //*

    // 降采样, 执行降采样滤波,叶子大小1cm
    pcl::VoxelGrid<pcl::PointXYZ> vg;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    vg.setInputCloud(cloud);
    vg.setLeafSize(0.01f, 0.01f, 0.01f);
    vg.filter(*cloud_filtered);
    cout << "PointCloud after filtering has: " << cloud_filtered->points.size() << " data points." << endl;

    // 创建平面模型分割器并初始化参数
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);

    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setMaxIterations(100);
    seg.setDistanceThreshold(0.02);

    // 循环剔除 尽可能多的平面
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::ExtractIndices<pcl::PointXYZ> extract;

    int i = 0, nr_points = (int) cloud_filtered->points.size();
    while (cloud_filtered->points.size() > 0.3 * nr_points) {
        // 移除剩余点云中最大的平面
        seg.setInputCloud(cloud_filtered);
        // 执行分割，将分割出来的平面点云索引保存到inliers中
        seg.segment(*inliers, *coefficients);
        if (inliers->indices.size() == 0) {
            cout << "Could not estimate a planar model for the given dataset." << endl;
            break;
        }
        // 从输入点云中取出平面内点
        extract.setInputCloud(cloud_filtered);
        extract.setIndices(inliers);
        extract.setNegative(false);
        // 得到与平面相关的点cloud_plane
        extract.filter(*cloud_plane);
        cout << "PointCloud representing the planar component: " << cloud_plane->points.size() << " data points."
             << endl;

        // 从点云中剔除这些平面内点，提取出剩下的点保存到cloud_f中，并重新赋值给cloud_filtered。
        extract.setNegative(true);
        extract.filter(*cloud_f);
        *cloud_filtered = *cloud_f;
    }

    // 从此时的点云(不包含平面)中提取簇
    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setClusterTolerance(0.02); // 设置临近搜索的搜索半径（搜索容差）为2cm
    ec.setMinClusterSize(100);    // 每个簇（集群）的最小大小
    ec.setMaxClusterSize(25000);  // 每个簇（集群）的最大大小

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud_filtered);
    ec.setSearchMethod(tree);// 设置点云搜索算法

    ec.setInputCloud(cloud_filtered);   // 设置输入点云
    ec.extract(cluster_indices);        // 设置提取到的簇，将每个簇以索引的形式保存到cluster_indices;

    // 可视化 每个簇
    // pcl::PCDWriter writer;
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    int j = 0;
    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin();
         it != cluster_indices.end(); ++it) {

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
        const std::vector<int> &indices = it->indices;

        for (std::vector<int>::const_iterator pit = indices.begin(); pit != indices.end(); ++pit)
            cloud_cluster->points.push_back(cloud_filtered->points[*pit]);

        cloud_cluster->width = cloud_cluster->points.size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;

        std::cout << "PointCloud representing the Cluster: " << cloud_cluster->points.size() << " data points."
                  << std::endl;
        /*
            std::stringstream ss;
            ss << "cloud_cluster_" << j << ".pcd";
            writer.write<pcl::PointXYZ>(ss.str(), *cloud_cluster, false); //
        */
        std::stringstream ss;
        ss << "cloud_cluster_" << j;
        // Generate a random (bright) color
        pcl::visualization::PointCloudColorHandlerRandom<pcl::PointXYZ> single_color(cloud_cluster);
        viewer->addPointCloud<pcl::PointXYZ>(cloud_cluster, single_color, ss.str());
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, ss.str());

        j++;
    }
    std::cout << "cloud size: " << cluster_indices.size() << std::endl; // 总共有多少个 簇

    viewer->addCoordinateSystem(0.5);

    while(!viewer->wasStopped()){
        viewer->spinOnce();
    }


    return 0;
}




