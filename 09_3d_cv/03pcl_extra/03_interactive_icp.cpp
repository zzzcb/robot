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

bool next_iteration = false;

void keyboardEventOccurred(const pcl::visualization::KeyboardEvent &event, void *nothing) {
    if (event.getKeySym() == "n" && event.keyDown()) // n键 按下
        next_iteration = true;
}

int main(int argc, char **argv) {

    PointCloudT::Ptr cloud(new PointCloudT);      // 原始点云         | target
    PointCloudT::Ptr cloud_trans(new PointCloudT);// 手动变换后的点云   |input
    PointCloudT::Ptr cloud_icp(new PointCloudT);  // icp 配准后的点云  | 和input向target变换后的input点云差不多

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
    if (pcl::io::loadPLYFile(argv[1], *cloud) < 0) {
        PCL_ERROR ("Error loading cloud %s.\n", argv[1]);
        return (-1);
    }
    std::cout << "\nLoaded file " << argv[1] << " (" << cloud->size() << " points) in " << time.toc() << " ms\n"
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
    pcl::transformPointCloud(*cloud, *cloud_trans, trans_matrix);

    //3 icp 配准 cloud_trans 向 cloud
    time.tic();
    pcl::IterativeClosestPoint<PointT, PointT> icp;
    icp.setMaximumIterations(iterations);
    icp.setInputSource(cloud_trans);
    icp.setInputTarget(cloud);
    icp.align(*cloud_icp);// 执行配准, 输出结果到 cloud_icp


    cout << "Applied " << iterations << " ICP iteration(s) in " << time.toc() << " ms" << endl;
//    cout << "cloud_icp size" << cloud_icp->points.size() << endl;
//    pcl::io::savePLYFile("../data/cloud_trans.ply", *cloud_trans);
//    pcl::io::savePLYFile("../data/cloud.ply", *cloud);
//    pcl::io::savePLYFile("../data/cloud_icp.ply", *cloud_icp);

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

    //4 可视化展示
    //创建两个左右视图,
    //左视图是input+target 原始点云(cloud_trans,cloud)
    //右视图是icp + target(cloud_icp,cloud)
    pcl::visualization::PCLVisualizer viewer("Interactive ICP");
    int v1(0);
    int v2(1);
    viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1); // 左半面
    viewer.createViewPort(0.5, 0.0, 1.0, 1.0, v2); // 右半面

    float black = 0.0;
    float white = 1.0 - black;

    // 左右两边分别显示 cloud(目标) 白色
    pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_white(cloud, (int) 255 * white,
                                                                         (int) 255 * white, (int) 255 * white);
    viewer.addPointCloud(cloud, cloud_white, "cloud_in_v1", v1);
    viewer.addPointCloud(cloud, cloud_white, "cloud_in_v2", v2);

    // 左面显示 cloud_trans(原始输入) 绿色
    pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_trans_green(cloud_trans, 20, 180, 20);
    viewer.addPointCloud(cloud_trans, cloud_trans_green, "cloud_tr_v1", v1);

    // 右面显示 cloud_icp(不断变化) 红色
    pcl::visualization::PointCloudColorHandlerCustom<PointT> cloud_icp_red(cloud_icp, 180, 20, 20);
    viewer.addPointCloud(cloud_icp, cloud_icp_red, "cloud_icp_v2", v2);

    // Adding text descriptions in each viewport
    viewer.addText("White: target cloud\nGreen: init input cloud", 10, 15, 16, white, white, white, "v1_info", v1);
    viewer.addText("White: target cloud\nRed: icp cloud", 10, 15, 16, white, white, white, "v2_info", v2);

    std::stringstream ss;
    ss << iterations;
    std::string iterations_cnt = "ICP iterations = " + ss.str();
    viewer.addText(iterations_cnt, 10, 60, 16, white, white, white, "iterations_cnt", v2);

    // Set background color
    viewer.setBackgroundColor(black, black, black, v1);
    viewer.setBackgroundColor(black, black, black, v2);

    // Set camera position and orientation
    viewer.setCameraPosition(-3.68332, 2.94092, 5.71266, 0.289847, 0.921947, -0.256907, 0);
    viewer.setSize(1280, 1024);  // Visualiser window size

    //5 用户每按下 一次空格 就进行一次迭代
    viewer.registerKeyboardCallback(&keyboardEventOccurred, (void *) NULL);

    cout << "==============================================" << endl;

    icp.setMaximumIterations(1); // 为下面 按键一次迭代一次 准备
    *cloud_trans = *cloud_icp;   // 用户按键迭代时 使用

    while (!viewer.wasStopped()) {
        viewer.spinOnce(100);

        if (next_iteration) {
            time.tic();
            icp.align(*cloud_icp);
            cout << "---" << endl;
            cout << "Applied 1 ICP iteration in " << time.toc() << " ms" << endl;
            if (icp.hasConverged()) {
                cout << "收敛,评分是 " << icp.getFitnessScore() << endl;
                cout << "input -> target 的变换矩阵是 \n" << icp.getFinalTransformation() << endl;
                *cloud_trans = *cloud_icp; // 为下次 trans -> cloud 准备

                ss.str("");
                ss << ++iterations;
                std::string iterations_cnt = "ICP iterations = " + ss.str();
                viewer.updateText(iterations_cnt, 10, 60, 16, white, white, white, "iterations_cnt");
                viewer.updatePointCloud(cloud_icp, cloud_icp_red, "cloud_icp_v2");
            } else {
                PCL_ERROR("\nICP 已经不再收敛\n");
                return (-1);
            }
            next_iteration = false;
        }
    }

    return 0;
}

