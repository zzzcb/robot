//
// Created by zcb on 5/12/21.
//
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

/*
 * 图片修复
 */
cv::Mat mask;

void mouse_cb(int event, int x, int y, int flags, void *userdata) {
    //event : cv::MouseEventTypes
    //flags : cv::MouseEventFlags
    // 左键按下 且 移动
    if (event == cv::EVENT_MOUSEMOVE && flags == cv::EVENT_FLAG_LBUTTON) {
        cv::circle(mask, cv::Point(x, y), 5, cv::Scalar(255), -1);
    }
    // 右键按下
    if (flags == cv::EVENT_FLAG_RBUTTON) {
        cv::Mat src = *(cv::Mat *) userdata;
        cv::inpaint(src, mask, src, 5, cv::INPAINT_NS);
        cv::imshow("src", src);
    }


}


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_project/images/itheima_inpaint.jpg");
    cv::imshow("src", src);

    mask = cv::Mat::zeros(src.size(), CV_8UC1);
    cv::setMouseCallback("src", mouse_cb, &src);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}