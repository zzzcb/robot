//
// Created by zcb on 6/12/21.
//
/*
 * icp 点云配准
 * http://robot.czxy.com/docs/pcl/chapter03/registration/
 */

#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>  // icp 点云配准

#include <cstdlib>
#include <ctime>

using namespace std;

float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}

void print_cloud_point(pcl::PointCloud<pcl::PointXYZ> cloud) {
    for (int i = 0; i < cloud.points.size(); ++i) {
        cout <<
             cloud.points[i].x << " " <<
             cloud.points[i].y << " " <<
             cloud.points[i].z << endl;
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_input(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_target(new pcl::PointCloud<pcl::PointXYZ>);

    //1 随机生成5 个点
    cloud_input->width = 5;
    cloud_input->height = 1;
    cloud_input->points.resize(cloud_input->width * cloud_input->height);
    for (int i = 0; i < cloud_input->points.size(); ++i) {
        cloud_input->points[i].x = random_float();
        cloud_input->points[i].y = random_float();
        cloud_input->points[i].z = random_float();
    }
    //cout << "cloud_input 点的个数 " << cloud_input->points.size() << endl;
    cout << "cloud input的 点 " << endl;
    print_cloud_point(*cloud_input);

    //2 手动模拟cloud_target(真实情景下,cloud_input 和 cloud_target 是不同角度获取的数据)
    *cloud_target = *cloud_input;//复制cloud_input 到cloud_target
    for (int i = 0; i < cloud_target->points.size(); ++i) {
        cloud_target->points[i].x += 0.7f;
    }
    cout << "cloud target的 点 " << endl;
    print_cloud_point(*cloud_target);

    // 我们所要做的工作是 求出 cloud_input 到 cloud_target 的变换矩阵

    //3 创建ICP对象,Iterative Closet Point
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(cloud_input);
    icp.setInputTarget(cloud_target);

    pcl::PointCloud<pcl::PointXYZ> output;
    icp.align(output); // 配准

    cout << "output的 点 " << endl;
    print_cloud_point(output);
    //cout << "output 的size " << output.points.size() << endl;

    cout << "是否收敛 " << icp.hasConverged() << endl;
    cout << "评分(越小越好) " << icp.getFitnessScore() << endl;
    cout << "input 到 target 的变换矩阵 \n" << icp.getFinalTransformation() << endl;

    return 0;
}














