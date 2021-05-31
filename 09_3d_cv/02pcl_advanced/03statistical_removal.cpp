//
// Created by zcb on 5/31/21.
//

/*
 * 离群点的移除: statistical removal, 更适合采集好的数据的移除，不适合实时的数据移除.
 * 精度高,速度慢
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/statistical_outlier_removal.h>

int main() {
    //  pcl::PCLPointCloud2 不需要指定 数据类型,比 pcl::PointCloud 好
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2()); // 降采样后的点云

    //1. 从文件中 读取点云数据
    pcl::PCDReader pcdReader;
    pcdReader.read("../data/table_scene_lms400.pcd", *cloud);


    //2 创建统计学离群点移除器
    pcl::StatisticalOutlierRemoval<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setMeanK(50); // 最近邻的点的个数 K
    sor.setStddevMulThresh(1.0); // 标准差的倍数，不要太大，太大了过滤不掉了
    //sor.setNegative(true);// 此时是 保留在 区间的两边

    std::cout << "过滤前点云的数量: " << cloud->width * cloud->height
              << " 点云的字段列表: " << pcl::getFieldsList(*cloud)
              << std::endl;

    //3 进行过滤
    sor.filter(*cloud_filtered);

    std::cout << "过滤后点云的数量: " << cloud_filtered->width * cloud_filtered->height
              << std::endl;

    //4 保存点云到文件
    pcl::PCDWriter pcdWriter;
    pcdWriter.writeBinaryCompressed("../data/test.pcd", *cloud_filtered);

}

