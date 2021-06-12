//
// Created by zcb on 6/12/21.
//

/*
 * 交互式的 icp 点云配准
 * http://robot.czxy.com/docs/pcl/chapter03/registration_interactive_icp/#icp
 */

#include <iostream>
//#include <pcl/io/io.h> // 其实没有必要 导pcl/io/io.h ,导入pcl/point_types.h就行了
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h> // 加载 ply 文件
#include <pcl/console/time.h> // 提供 TicToc

#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

int main(int argc, char **argv) {

    PointCloudT::Ptr cloud_input(new PointCloudT);// 原始点云         | target
    PointCloudT::Ptr cloud_trans(new PointCloudT);// 手动变换后的点云   |input
    PointCloudT::Ptr cloud_icp(new PointCloudT);  // icp 配准后的点云  | 和input差不多

    // Checking program arguments
    if (argc < 2) {
        printf("Usage :\n");
        printf("\t\t%s file.ply number_of_ICP_iterations\n", argv[0]);
        PCL_ERROR ("Provide one ply file.\n");
        return (-1);
    }
    int iterations = 1;  // Default number of ICP iterations
    if (argc > 2) {
        // If the user passed the number of iteration as an argument
        iterations = atoi(argv[2]);
        if (iterations < 1) {
            PCL_ERROR ("Number of initial iterations must be >= 1\n");
            return (-1);
        }
    }

    //1 加载点云
    pcl::console::TicToc time;
    time.tic();
    if (pcl::io::loadPLYFile(argv[1], *cloud_input) < 0) {
        PCL_ERROR ("Error loading cloud %s.\n", argv[1]);
        return (-1);
    }
    std::cout << "\nLoaded file " << argv[1] << " (" << cloud_input->size() << " points) in " << time.toc() << " ms\n"
              << std::endl;

    //2 对原始点云 进行刚性变换(旋转,平移) 绕z轴 旋转theta,沿z轴平移0.4
    Eigen::Matrix4d trans_matrix = Eigen::Matrix4d::Identity();
    double theta = M_PI / 6;
    trans_matrix(0, 0) = cos(theta);
    trans_matrix(0, 1) = -sin(theta);
    trans_matrix(1, 0) = sin(theta);
    trans_matrix(1, 1) = cos(theta);
    trans_matrix(2, 3) = 0.4;
    cout << "trans_matrix: \n" << trans_matrix << endl;
    //执行刚性变换
    pcl::transformPointCloud(*cloud_input, *cloud_trans, trans_matrix);

    //3 icp 配准 cloud_trans 向 cloud_input
    time.tic();
    pcl::IterativeClosestPoint<PointT, PointT> icp;
    icp.setMaximumIterations(iterations);
    icp.setInputSource(cloud_trans);
    icp.setInputTarget(cloud_input);
    icp.align(*cloud_icp);// 执行配准, 输出结果到 cloud_icp
    cout << "Applied " << iterations << " ICP iteration(s) in " << time.toc() << " ms" << endl;
//    cout << "cloud_icp size" << cloud_icp->points.size() << endl;
//    pcl::io::savePLYFile("../data/cloud_trans.ply",*cloud_trans);
//    pcl::io::savePLYFile("../data/cloud_input.ply",*cloud_input);
//    pcl::io::savePLYFile("../data/cloud_icp.ply",*cloud_icp);

    //检查ICP算法是否收敛;否则退出程序
    //如果返回true,我们将转换矩阵存储在4x4矩阵中,然后打印刚性矩阵转换(从input -> target)
    if (icp.hasConverged()) {
        cout << "是收敛" << endl;
        cout << "迭代的次数 " << iterations << endl;
        cout << "评分 " << icp.getFitnessScore() << endl;
        cout << "input -> target 的变换矩阵是 \n" << icp.getFinalTransformation() << endl;
    } else {
        PCL_ERROR ("\nICP 没有收敛\n");
        return (-1);
    }


    return 0;
}


