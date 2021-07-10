//
// Created by zcb on 7/8/21.
//
/*
 * 相机内参标定
 * 根据前面收集好的图片进行相机标定
 */
/*
 *  相机标定
 *  1. 读取所有的图片
 *  2. 遍历获取每个图片的角点(像素坐标uv)
 *  3. 通过亚像素优化角点的位置
 *  4. 创建对应的世界坐标(XYZw)
 *  5. 执行标定操作
 *  6. 保存标定的结果到文件中
 */
// opencv
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

void getWorldPoints(cv::Size &patternSize, float square_size, vector<cv::Point3f> &points) {
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

void saveToFile(cv::String filename, cv::Mat &cameraMatrix, cv::Mat &distCoeffs, double r_mse, cv::Size &imgSize) {
    // 获取当前时间
    time_t tm;
    time(&tm);
    struct tm *t2 = localtime(&tm);
    char buf[1024];
    strftime(buf, sizeof(buf), "%c", t2);

    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs << "image_size" << imgSize; // 像素
    fs << "calibration_time" << buf;// key -val
    fs << "camera_in_matrix" << cameraMatrix;
    fs << "dist_coeffs" << distCoeffs;
    fs << "r_mse" << r_mse;
    fs.release();

}

int main(int argc, char **argv) {

    cv::Size patternSize(6, 9); // 棋盘的角点 size
    float square_size = 0.02; // 每个 棋盘格子的 大小,单位m

    vector<vector<cv::Point2f>> pixelPoints; // 所有 像素坐标系uv下的点
    vector<vector<cv::Point3f>> worldPoints;//所有 世界坐标系下的点,取标定板的平面为xy,原点设置在第一个角点

    //1. 读取所有的图片 使用cv::glob
    vector<cv::String> paths;// 传出参数 所有的图片路径
    cv::glob("/home/zcb/gazebo_camera_calibration/src/common_pkg/images/pic*.png", paths);
    int idx = 0;
    cv::Size imgSize;
    for (auto path:paths) {
        cv::Mat src = cv::imread(path);
        imgSize = src.size();

        //2. 查找角点
        vector<cv::Point2f> corners;
        bool isFound;
        findCorners(src, patternSize, isFound, corners);
//        // 画出角点
//        cv::drawChessboardCorners(src, patternSize, corners, isFound);
//        cv::imshow("img" + to_string(idx++), src);
//        cv::waitKey(0);
//        cv::destroyAllWindows();

        // 得到 该图片上角点 在相机坐标系下的坐标
        vector<cv::Point3f> points;
        getWorldPoints(patternSize, square_size, points);
        if (isFound) {
            pixelPoints.push_back(corners);
            worldPoints.push_back(points);
        }
    }
    //5 相机标定(前面已经拿到了每张图片的 pixelPoints 和 worldPoints)
    cv::Mat cameraInMatrix;// 相机内参  fx(f/dx) fy(f/dy) u0 v0 | 相机内参: camera frame -> uv frame
    cv::Mat distCoeffs;    // 畸变参数 k1 k2 p1 p2 k3  // distortion coefficients

    vector<cv::Mat> rvecs; // 世界坐标系到相机坐标系 的（姿态） // 外参
    vector<cv::Mat> tvecs; // 世界坐标系到相机坐标系 的（位置）

    double r_mse = cv::calibrateCamera(worldPoints, pixelPoints, imgSize, cameraInMatrix, distCoeffs, rvecs, tvecs);

    cout << "r_mse";
    cout << r_mse << endl;

    cout << "camera in matrix";
    cout << cameraInMatrix << endl;

    cout << "dist coeffs";
    cout << distCoeffs << endl;

//    cout << "==="<<endl;
//    for(int i=0;i<rvecs.size();i++){
//        cout <<rvecs[i]<<endl;
//        cout <<tvecs[i]<<endl;
//        cout << "---"<<endl;
//    }

    //6 保存相机内参数据到 文件
    if (cv::checkRange(cameraInMatrix) && cv::checkRange(distCoeffs)) {
        saveToFile("/home/zcb/gazebo_camera_calibration/src/common_pkg/calibration_result/camera_in.xml",
                   cameraInMatrix, distCoeffs,
                   r_mse, imgSize);
        saveToFile("/home/zcb/gazebo_camera_calibration/src/common_pkg/calibration_result/camera_in.yml",
                   cameraInMatrix, distCoeffs,
                   r_mse, imgSize);
    } else {
        cout << "标定失败" << endl;
    }


    return 0;
}
