//
// Created by zcb on 5/30/21.
//

#include <iostream>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

void oneOff(pcl::visualization::PCLVisualizer &visualizer) {
    // 只会执行一次
    // 设置背景为 红色
    visualizer.setBackgroundColor(1.0, 0.5, 1.0);

    // 添加一个球  圆心为值(1,0,0) 半径为 0.25
    pcl::PointXYZ c;
    c.x = 1;
    c.y = 0;
    c.z = 0;
    visualizer.addSphere(c, 0.25, "sphere", 0);
}

int user_data = 0;

void psycho(pcl::visualization::PCLVisualizer &visualizer) {
    static unsigned int cnt = 0;
    std::stringstream ss;
    ss << "loop: " << cnt;
    cnt++;

    visualizer.removeShape("text");
    visualizer.addText(ss.str(), 200, 300, "text", 0);// 不能直接覆盖,所以需要上面一行代码

    cout <<"while loop"<< user_data << endl;
}


int main() {

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    pcl::io::loadPCDFile("../data/pcl_logo.pcd", *cloud);

    pcl::visualization::CloudViewer viewer("Cloud Viewer by zcb");
    viewer.showCloud(cloud); // 这行 代码可能会阻塞一会儿

    viewer.runOnVisualizationThreadOnce(oneOff); // 只调用一次
    viewer.runOnVisualizationThread(psycho); // 一直调用

    while (!viewer.wasStopped()) { //while 的调用频率 远大于 上面的 psycho
        user_data++;
    }

    return 0;
}










