//
// Created by zcb on 5/31/21.
//

/*
 * 离群点的移除: condition removal 条件滤波, 更适合实时的数据移除.
 * 精度低,速度快
 */


#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/conditional_removal.h>


#include <cstdlib>
#include <ctime>

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}

int main() {
    srand(time(NULL));

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    //1. 准备 点云
    cloud->width = 100;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    // 随机生成100 个点
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].x = random_float();
        cloud->points[i].y = random_float();
        cloud->points[i].z = random_float();
    }


    //2 创建 半径离群值滤波
    pcl::ConditionalRemoval<pcl::PointXYZ> cr;
    // 0 < z <= 0.8
    pcl::ConditionAnd<pcl::PointXYZ>::Ptr cond_and(new pcl::ConditionAnd<pcl::PointXYZ>());
    cr.setInputCloud(cloud);
//    cr.setKeepOrganized(true); // 设置保持点云的结构,去掉的数字用 nan 代替

    pcl::FieldComparison<pcl::PointXYZ>::ConstPtr com1(
            new pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::GT, 0.0));
    pcl::FieldComparison<pcl::PointXYZ>::ConstPtr com2(
            new pcl::FieldComparison<pcl::PointXYZ>("z", pcl::ComparisonOps::LE, 0.8));
    cond_and->addComparison(com1);
    cond_and->addComparison(com2);

    cr.setCondition(cond_and);


    std::cout << "过滤前点云的数量: " << cloud->width * cloud->height
              << " 点云的字段列表: " << pcl::getFieldsList(*cloud)
              << std::endl;

    //3 进行过滤
    cr.filter(*cloud_filtered);

    std::cout << "过滤后点云的数量: " << cloud_filtered->width * cloud_filtered->height
              << std::endl;

    //4 保存点云到文件
    pcl::PCDWriter pcdWriter;
    pcdWriter.writeBinaryCompressed("../data/test.pcd", *cloud_filtered);

}

