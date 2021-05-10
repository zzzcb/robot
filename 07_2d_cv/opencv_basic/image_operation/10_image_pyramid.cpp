//
// Created by zcb on 5/8/21.
//

/*
 * 图片 金字塔 http://robot.czxy.com/docs/opencv/01_opencv_basic/04_jihebianhuan/#_10
 * 金字塔下采样 和  直接进行resize操作他们之间有什么差别?
   当我们对图片进行下采样操作的时候,即使图片变得非常小,我们任然能够看到它的轮廓,这对后面我们进行机器学习是非常重要的一步操作
   ,而当我们直接使用resize进行操作的时候,我们发现图片似乎不能完全表示它原有的轮廓,出现了很多的小方块!
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat src = cv::imread("/home/zcb/cv2/opencv_basic/images/lena.jpg");


    cv::Mat dst2; // 1/2
    cv::pyrDown(src,dst2,cv::Size());

    cv::Mat dst4; // 1/4
    cv::pyrDown(dst2,dst4,cv::Size());

    cv::imshow("src",src);
    cv::imshow("dst2",dst2);
    cv::imshow("dst4",dst4);


    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

