/*
点云的平移和旋转 即 transform
*/
#include <iostream>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

int main(int argc, char **argv) {

    //1 加载点云
    pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud(new pcl::PointCloud<pcl::PointXYZ>());

    if (pcl::io::loadPCDFile(argv[1], *source_cloud) < 0) {
        std::cout << "Error loading point cloud " << argv[1] << std::endl << std::endl;
        return -1;
    }


    /* 2 使用Affine3f
    */
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();

    float theta = M_PI / 4;  // 绕 z 轴 逆时针 旋转 45度
    transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));

    transform.translation() << 0.5, 0, 0; // 沿 x移动0.5m
    // std::cout << "transform matrix: " <<transform.matrix() << std::endl;


    //3 进行变换操作: 顺序是 先旋转 后平移!
    pcl::PointCloud<pcl::PointXYZ>::Ptr dst_cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::transformPointCloud(*source_cloud, *dst_cloud, transform);

    //4 展示 变换 前后的 点云
    pcl::visualization::PCLVisualizer visualizer("visualizer by zcb");

    // 显示 坐标轴
    visualizer.addCoordinateSystem(1);

    // 变换 前
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_color(source_cloud, 0, 255, 0);
    visualizer.addPointCloud<pcl::PointXYZ>(source_cloud, source_color, "source_cloud");
    visualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,
                                                "source_cloud"); // 设置点的大小
    // 变换 后
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> dst_color(dst_cloud, 0, 0, 255);
    visualizer.addPointCloud<pcl::PointXYZ>(dst_cloud, dst_color, "dst_cloud");
    visualizer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2,
                                                "dst_cloud"); // 设置点的大小

    while (!visualizer.wasStopped()) {
        visualizer.spinOnce();
    }


    return 0;
}

