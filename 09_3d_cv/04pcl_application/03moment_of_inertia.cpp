//
// Created by zcb on 6/14/21.
//
/*
 * 3d 包容盒
 * http://robot.czxy.com/docs/pcl/chapter04/bounding_volumes/#3d
 */

#include <vector>
#include <thread>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    if (argc != 2)
        return (0);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    if (pcl::io::loadPCDFile(argv[1], *cloud) == -1)
        return (-1);

    // 创建惯性矩估算对象，设置输入点云，并进行计算
    pcl::MomentOfInertiaEstimation<pcl::PointXYZ> feature_extractor;
    feature_extractor.setInputCloud(cloud);
    feature_extractor.compute();

    std::vector<float> moment_of_inertia;
    std::vector<float> eccentricity;

    pcl::PointXYZ min_point_AABB; // AABB包容盒最小点位置, 两个对角点可以确定,因为轴向已经确定了
    pcl::PointXYZ max_point_AABB; // AABB包容盒最大点位置

    pcl::PointXYZ min_point_OBB; // obb 需要一个方向
    pcl::PointXYZ max_point_OBB;
    Eigen::Matrix3f rotational_matrix_OBB;

    pcl::PointXYZ position_OBB;

    float major_value, middle_value, minor_value;
    Eigen::Vector3f major_vector, middle_vector, minor_vector;
    Eigen::Vector3f mass_center;

    // 获取惯性矩
    feature_extractor.getMomentOfInertia(moment_of_inertia);
    // 获取离心率
    feature_extractor.getEccentricity(eccentricity);
    // 获取AABB盒子
    feature_extractor.getAABB(min_point_AABB, max_point_AABB); // obb 需要一个方向
    // 获取OBB盒子
    feature_extractor.getOBB(min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);
    feature_extractor.getEigenValues(major_value, middle_value, minor_value);
    // 获取主轴major_vector，中轴middle_vector，辅助轴minor_vector
    feature_extractor.getEigenVectors(major_vector, middle_vector, minor_vector);
    // 获取质心
    feature_extractor.getMassCenter(mass_center);

    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();
    viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
    // 添加AABB包容盒
    viewer->addCube(min_point_AABB.x, max_point_AABB.x, min_point_AABB.y,
                    max_point_AABB.y, min_point_AABB.z, max_point_AABB.z, 1.0, 1.0, 0.0, "AABB");
    viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION,
                                        pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, "AABB");

    // 添加OBB包容盒
    Eigen::Vector3f position(position_OBB.x, position_OBB.y, position_OBB.z);
    Eigen::Quaternionf quat(rotational_matrix_OBB);
    // position：中心位置
    // quat：旋转矩阵
    // max_point_OBB.x - min_point_OBB.x  宽度
    // max_point_OBB.y - min_point_OBB.y  高度
    // max_point_OBB.z - min_point_OBB.z  深度
    viewer->addCube(position, quat, max_point_OBB.x - min_point_OBB.x, max_point_OBB.y - min_point_OBB.y,
                    max_point_OBB.z - min_point_OBB.z, "OBB");
    viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION,
                                        pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, "OBB");

    pcl::PointXYZ center(mass_center(0), mass_center(1), mass_center(2));
    pcl::PointXYZ x_axis(major_vector(0) + mass_center(0), major_vector(1) + mass_center(1),
                         major_vector(2) + mass_center(2));
    pcl::PointXYZ y_axis(middle_vector(0) + mass_center(0), middle_vector(1) + mass_center(1),
                         middle_vector(2) + mass_center(2));
    pcl::PointXYZ z_axis(minor_vector(0) + mass_center(0), minor_vector(1) + mass_center(1),
                         minor_vector(2) + mass_center(2));
    viewer->addLine(center, x_axis, 1.0f, 0.0f, 0.0f, "major eigen vector");
    viewer->addLine(center, y_axis, 0.0f, 1.0f, 0.0f, "middle eigen vector");
    viewer->addLine(center, z_axis, 0.0f, 0.0f, 1.0f, "minor eigen vector");

    while (!viewer->wasStopped()) {
        viewer->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }

    return (0);
}