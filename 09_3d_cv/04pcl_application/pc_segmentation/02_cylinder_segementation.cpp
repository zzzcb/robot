//
// Created by zcb on 6/13/21.
//
/*
 * 点云分割-- 圆柱体模型分割
 * http://robot.czxy.com/docs/pcl/chapter04/segmentation/#_6
 */
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

using namespace std;

int main(int argc, char **argv) {

    //1 加载点云
    pcl::PCDReader reader;
    PointCloudT::Ptr cloud(new PointCloudT);
    reader.read("../data/table_scene_mug_stereo_textured.pcd", *cloud);
    cout << "cloud点云有 " << cloud->points.size() << " 个点" << endl;

    //2 直通滤波 去掉远处的点
    pcl::PassThrough<PointT> pass;
    PointCloudT::Ptr cloud_filtered(new PointCloudT);
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");//z 方向
    pass.setFilterLimits(0, 1.5); // 保留 0 - 1.5
    pass.filter(*cloud_filtered);
    cout << "cloud_filtered点云有 " << cloud_filtered->points.size() << " 个点" << endl;

    //3 估算法线
    pcl::NormalEstimation<PointT, pcl::Normal> ne;
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>);
    ne.setSearchMethod(tree);// kd tree
    ne.setInputCloud(cloud_filtered);
    ne.setKSearch(50); // 50 个邻居
    ne.compute(*cloud_normals);

    //===============平面================
    //4 创建平面模型分割器
    pcl::SACSegmentationFromNormals<PointT, pcl::Normal> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_NORMAL_PLANE);
    seg.setNormalDistanceWeight(0.1);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setMaxIterations(100);
    seg.setDistanceThreshold(0.03);
    seg.setInputCloud(cloud_filtered);
    seg.setInputNormals(cloud_normals);

    pcl::ModelCoefficients::Ptr
            coefficients_plane(new pcl::ModelCoefficients),
            coefficients_cylinder(new pcl::ModelCoefficients); // 两个模型系数
    pcl::PointIndices::Ptr
            inliers_plane(new pcl::PointIndices),
            inliers_cylinder(new pcl::PointIndices); // 两个 inliers 索引,符合模型的索引
    seg.segment(*inliers_plane, *coefficients_plane);
    cout << "Plane coefficients: " << *coefficients_plane << endl;

    //5 提取inliers_plane 中的点
    pcl::ExtractIndices<PointT> extract;                        // 点提取对象
    extract.setInputCloud(cloud_filtered);
    extract.setIndices(inliers_plane);
    extract.setNegative(false); //不取反 // 默认是取反的

    //6 保存平面的 点 到文件
    pcl::PCDWriter writer;
    pcl::PointCloud<PointT>::Ptr cloud_plane(new pcl::PointCloud<PointT>());
    extract.filter(*cloud_plane);
    cout << "PointCloud representing the planar component: " << cloud_plane->points.size() << " data points." << endl;
    writer.write("../data/table_scene_mug_stereo_textured_plane.pcd", *cloud_plane, false);

    //===============圆柱体================
    //7 准备非平面部分的 点和法线
    extract.setNegative(true); // 所有非 平面的地方 点
    pcl::PointCloud<PointT>::Ptr cloud_filtered2(new pcl::PointCloud<PointT>());
    extract.filter(*cloud_filtered2);

    pcl::ExtractIndices<pcl::Normal> extract_normals;// 法线提取对象
    extract_normals.setInputCloud(cloud_normals);
    extract_normals.setIndices(inliers_plane);
    extract_normals.setNegative(true); // 取非平面部分的法线
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals2(new pcl::PointCloud<pcl::Normal>);
    extract_normals.filter(*cloud_normals2);

    //8 创建平面模型分割器
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_CYLINDER);   // 设置分割模型为圆柱体
    seg.setMethodType(pcl::SAC_RANSAC);         // 设置采用RANSAC算法进行参数估计
    seg.setNormalDistanceWeight(0.1);           // 设置表面法线权重系数
    seg.setMaxIterations(10000);                // 设置最大迭代次数10000
    seg.setDistanceThreshold(0.05);             // 设置内点到模型的最大距离 0.05m
    seg.setRadiusLimits(0, 0.1);                // 设置圆柱体的半径范围0 -> 0.1m
    seg.setInputCloud(cloud_filtered2);
    seg.setInputNormals(cloud_normals2);

    seg.segment(*inliers_cylinder, *coefficients_cylinder);
    cout << "Cylinder coefficients: " << *coefficients_cylinder << endl;

    //9 保存圆柱体的 点 到文件
    extract.setInputCloud(cloud_filtered2);// 非平面的点
    extract.setIndices(inliers_cylinder);
    extract.setNegative(false);
    pcl::PointCloud<PointT>::Ptr cloud_cylinder(new pcl::PointCloud<PointT>());
    extract.filter(*cloud_cylinder);
    cout << "PointCloud representing the cylinder component: " << cloud_cylinder->points.size() << " data points."<< endl;
    writer.write("../data/table_scene_mug_stereo_textured_cylinder.pcd", *cloud_cylinder, false);


    return 0;
}





