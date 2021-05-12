#include <iostream>
#include <opencv2/opencv.hpp>

int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");
    cv::imshow("lena.jpg", src);


    int key = cv::waitKey(0);// 0 是永远等待
    std::cout << key << std::endl;

    // 释放资源，销毁窗口
    cv::destroyAllWindows();


    return 0;
}