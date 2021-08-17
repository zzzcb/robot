//
// Created by zcb on 7/10/21.
//

/*
 * 在前两个的基础上进行相机外参标定(需要用到相机内参)
 */

// opencv
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Eigen/Eigen>

using namespace std;

void getWorldPoints(const cv::Size &patternSize, float square_size, vector<cv::Point3f> &points) {
    /*
     * x,y,z
     * [0,0,0] [1,0,0] [2,0,0] ... [5,0,0] * 0.02
     * [0,1,0] [1,1,0] [2,1,0] ... [5,1,0] * 0.02
     * .
     * .
     * .
     * [0,8,0]                 ... [5,8,0] * 0.02
     */
    for (int i = 0; i < patternSize.height; ++i) {
        for (int j = 0; j < patternSize.width; ++j) {
            points.push_back(cv::Point3f(j * square_size, i * square_size, 0));
        }
    }
}

void findCorners(cv::Mat &src, const cv::Size &patternSize, bool &isFound, vector<cv::Point2f> &corners) {
    // src,patternSize 传入参数
    // isFound,corners 传出参数

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    isFound = cv::findChessboardCorners(gray, patternSize, corners);
    if (isFound) {
        // 3 优化角点位置（只用于棋盘格）
        // 提高角点精度
        cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1);
        cv::cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
    }

}


void get_btg(vector<cv::Mat> &R_btg, vector<cv::Mat> &t_btg) {
    // R_btg 3x3 t_btg 3x1
    // 从ee_link_pose.xml中加载这些数据
    cv::FileStorage fs("/home/zcb/02gazebo_camera_calibration/src/camera_ex_cali_eyeonhand_pkg/ee_link_pose.xml",
                       cv::FileStorage::READ);

    for (int i = 0; i < 18; ++i) { // 0 -> 17
        cv::Mat temp;
        fs["pic" + to_string(i)] >> temp;//temp 4x4
        R_btg.push_back(temp(cv::Range(0, 3), cv::Range(0, 3)));// cv::Range 不含右端点
        t_btg.push_back(temp(cv::Range(0, 3), cv::Range(3, 4)));
    }

    fs.release();
}

void get_ctt(vector<cv::Mat> &R_ctt, vector<cv::Mat> &t_ctt) {

    //1 获取标定板的世界坐标
    vector<cv::Point3f> world_points;// 这时认为 标定板处就是世界坐标
    getWorldPoints(cv::Size(6, 9), 0.02, world_points);

    //2 获取相机内参矩阵 和 畸变系数 (从已经标定好的文件中获取)
    string camera_in_path = "/home/zcb/02gazebo_camera_calibration/src/camera_in_cali_pkg/calibration_result/camera_in.xml";// 相机内参
    cv::FileStorage fs(camera_in_path, cv::FileStorage::READ);
    cv::Mat camera_in_matrix, dist_coeffs;
    fs["camera_in_matrix"] >> camera_in_matrix; // 3x3
    fs["dist_coeffs"] >> dist_coeffs; //1x5

    string images_root = "/home/zcb/02gazebo_camera_calibration/src/camera_ex_cali_eyeonhand_pkg/images/";
    for (int i = 0; i < 18; ++i) { // 遍历图片
        string imgPath = images_root + "pic" + to_string(i) + ".png";
        cv::Mat src = cv::imread(imgPath);
        //3 获取每张图片的角点
        bool isFound;
        vector<cv::Point2f> corners;
        findCorners(src, cv::Size(6, 9), isFound, corners);

        //4 获取每张图片(target)的位姿
        cv::Mat rvec, tvec; // 都是 3x1
        cv::solvePnP(world_points, corners, camera_in_matrix, dist_coeffs, rvec, tvec);

        cv::Mat temp;
        cv::Rodrigues(rvec, temp); // 旋转向量 -> 转 为旋转矩阵
        R_ctt.push_back(temp);
        t_ctt.push_back(tvec);
    }

}

int main(int argc, char **argv) {

    //1. 准备btg(R,v) 旋转矩阵和平移向量  base T gripper,从base 的角度看 gripper
    vector<cv::Mat> R_btg, t_btg;
    get_btg(R_btg, t_btg);

    //2. 准备ctt(R,v) 旋转矩阵和平移向量  camera T target,从camera 的角度看 target
    vector<cv::Mat> R_ctt, t_ctt;
    get_ctt(R_ctt, t_ctt);

    //3 进行手眼标定
    cv::Mat R_gtc, t_gtc;// gripper T camera ,从gripper 的角度看 camera
    cv::calibrateHandEye(R_btg, t_btg, R_ctt, t_ctt, R_gtc, t_gtc,cv::HandEyeCalibrationMethod::CALIB_HAND_EYE_DANIILIDIS);

    cout << R_gtc << endl;
    cout << t_gtc << endl;


    return 0;
}













