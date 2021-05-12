//
// Created by zcb on 5/12/21.
//

/*
 * 证件照  替换背景
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_project/images/zhengjianzhao0.jpg");

    // 构建数据集
    cv::Mat data(src.rows * src.cols, src.channels(), CV_32F);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int idx = i * src.cols + j;
            cv::Vec3b colors = src.at<cv::Vec3b>(i, j);
            data.at<cv::Vec3f>(idx) = colors; // 某行 放 colors 三个数据
        }
    }

    int K = 4; // 分几类
    cv::Mat labels; // 输出的分类结果 ，类似于图像分水岭中的 marker
    cv::TermCriteria criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 10, 0.1);// 10 迭代次数 0.1 精度

    cv::kmeans(data, K, labels, criteria, 3,
               cv::KMEANS_RANDOM_CENTERS);// 3 是判断某个样本为某个类的最少聚类次数，比如值为3时，则某个样本聚类3次都为同一个类，则确定下来

    // 4 种颜色
    vector<cv::Vec3b> colors = {cv::Vec3b(255, 0, 0), cv::Vec3b(0, 255, 0), cv::Vec3b(0, 0, 255),
                                cv::Vec3b(0, 255, 255)};

    cv::Mat display(src.size(), CV_8UC3);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int idx = i * src.cols + j;
            int label = labels.at<int>(idx); // 获取 该 像素点的 label
            // 根据 label 修改颜色
            display.at<cv::Vec3b>(i, j) = colors[label];
        }
    }

//    cv::imshow("src", src);
//    cv::imshow("display", display);


    // 获取 0,0 位置的label
    int bg_label = labels.at<int>(0); // 背景的 label
//    cout << bg_label << endl;

    // 替换背景
    cv::imshow("src",src);
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int idx = i * src.cols + j;
            int label = labels.at<int>(idx); // 获取 该 像素点的 label
            if(label == bg_label){
                // 根据 label 修改颜色
                src.at<cv::Vec3b>(i, j) = cv::Vec3b(255,255,0); // 要替换成的 背景色
            }
        }
    }
    cv::imshow("dst",src);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
