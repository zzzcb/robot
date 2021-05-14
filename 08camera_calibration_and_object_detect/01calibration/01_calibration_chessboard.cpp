//
// Created by zcb on 5/14/21.
//
/*
 *  相机标定 使用 棋盘
 *  1. 读取所有的图片
 *  2. 遍历获取每个图片的角点(像素坐标uv)
 *  3. 通过亚像素优化角点的位置
 *  4. 创建对应的世界坐标(XYZw)
 *  5. 执行标定操作
 *  6. 保存标定的结果到文件中
 */
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void findCorners(cv::Mat &src, cv::Size &patternSize, bool &isFound, vector<cv::Point2f> &corners) {
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

void getPoints(cv::Size &patternSize, float square_size, vector<cv::Point3f> &points) {
    /*
     * [0,0,0] [1,0,0] [2,0,0] * 20
     * [0,1,0] [1,1,0] [2,1,0] * 20
     */
    for (int i = 0; i < patternSize.height; ++i) {
        for (int j = 0; j < patternSize.width; ++j) {
            points.push_back(cv::Point3f(j * square_size, i * square_size, 0));
        }
    }
}

void saveToFile(cv::String filename, cv::Mat &cameraMatrix, cv::Mat &distCoeffs, double r_mse,cv::Size& imgSize) {
    // 获取当前时间
    time_t tm;
    time(&tm);
    struct tm *t2 = localtime(&tm);
    char buf[1024];
    strftime(buf, sizeof(buf), "%c", t2);

    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs << "image_size" << imgSize; // 像素
    fs << "calibration_time" << buf;// key -val
    fs << "camera_matrix" << cameraMatrix;
    fs << "dist_coeffs" << distCoeffs;
    fs << "r_mse" << r_mse;
    fs.release();

}


int main() {
    cv::Size patternSize(6, 9); // 棋盘的角点 size
    float square_size = 20.0; // 每个 棋盘格子的 大小

    vector<vector<cv::Point2f>> imagePoints; // 所有 像素坐标系下的点
    vector<vector<cv::Point3f>> objectPoints; //所有 世界坐标系下的点,取标定板的平面为xy,原点设置在第一个角点

    cv::Size imgSize;


    //1. 读取所有的图片 使用cv::glob
    vector<cv::String> paths;// 传出参数 所有的图片路径
    cv::glob("/home/zcb/camera_calibration/01calibration/images/image_*.jpg", paths);// pattern 类似于正则
    int idx = 0;
    for (auto path:paths) {
//        cout << path << endl;
        cv::Mat src = cv::imread(path);
        imgSize = src.size();

        //2. 查找角点
        vector<cv::Point2f> corners;
        bool isFound;
        findCorners(src, patternSize, isFound, corners);
//        // 画出角点
//        cv::drawChessboardCorners(src, patternSize, corners, isFound);
//        cv::imshow("img" + to_string(idx++), src);


        // 得到 该图片的 世界真实坐标
        vector<cv::Point3f> points;
        getPoints(patternSize, square_size, points);
        if (isFound) {
            imagePoints.push_back(corners);
            objectPoints.push_back(points);
        }
    }

    // 5 相机标定
    cv::Mat cameraMatrix; // 相机内参  fx fy u0 v0
    cv::Mat distCoeffs; // 畸变参数 k1 k2 p1 p2 k3  // distortion coefficients
    vector<cv::Mat> rvecs; // 在相机坐标系的哪里 发现了 棋盘 (姿态)
    vector<cv::Mat> tvecs; // 在相机坐标系的哪里 发现了 棋盘 (位置)

    double r_mse = cv::calibrateCamera(objectPoints, imagePoints, imgSize, cameraMatrix, distCoeffs, rvecs, tvecs);


    cout << "r_mse";
    cout << r_mse << endl;

    cout << "camera matrix";
    cout << cameraMatrix << endl;

    cout << "dist coeffs";
    cout << distCoeffs << endl;

    //6 保存标定数据到 文件
    saveToFile("/home/zcb/camera_calibration/01calibration/01calibration_chessboard.xml", cameraMatrix, distCoeffs,
               r_mse,imgSize);
    saveToFile("/home/zcb/camera_calibration/01calibration/01calibration_chessboard.yml", cameraMatrix, distCoeffs,
               r_mse,imgSize);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

