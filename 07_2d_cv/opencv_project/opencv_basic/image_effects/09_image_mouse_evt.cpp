//
// Created by zcb on 5/10/21.
//

/*
 * 按下鼠标左键 移动 绘画
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

void mouse_cb(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_MOUSEMOVE && flags == cv::EVENT_FLAG_LBUTTON) {
        cout << "left button pressed moving" << endl;

        cv::Mat img = *(cv::Mat *) userdata;
        cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
        cv::imshow("src", img);

    }

}


int main() {

    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");


    cv::imshow("src", src);
    cv::setMouseCallback("src", mouse_cb, &src);


    cv::waitKey();
    cv::destroyAllWindows();

}
