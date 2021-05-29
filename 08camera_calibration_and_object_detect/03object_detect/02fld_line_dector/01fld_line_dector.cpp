/*
 * fld(fast line detector) 的出现是因为 lsd(line segment detctor)被申请了专利
 * 二者都是为了提高霍夫直线检测的速度,
 *
 */
#include <iostream>



#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, char **argv) {
    string in;
    cv::CommandLineParser parser(argc, argv,
                                 "{@input|../images/sudoku.jpg|input image}{help h||show help message}");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    in = parser.get<string>("@input");
    cv::Mat image_gray = imread(in, cv::IMREAD_GRAYSCALE);
    if (image_gray.empty()) {
        return -1;

    }



    // Create FLD detector
    // Param               Default value   Description
    // length_threshold    10            - Segments shorter than this will be discarded// 最小长度
    // distance_threshold  1.41421356    - A point placed from a hypothesis line //  距 假设线段 多远认为是 离群点
    //                                     segment farther than this will be
    //                                     regarded as an outlier
    // canny_th1           50            - First threshold for
    //                                     hysteresis procedure in Canny()
    // canny_th2           50            - Second threshold for
    //                                     hysteresis procedure in Canny()
    // canny_aperture_size 3             - Aperturesize for the sobel   // canny 卷积核的大小
    //                                     operator in Canny()
    // do_merge            false         - If true, incremental merging of segments  // 是否合并 相近的 线段
    //                                     will be perfomred
    int length_threshold = 10;
    float distance_threshold = 1.41421356f;
    double canny_th1 = 50.0;
    double canny_th2 = 50.0;
    int canny_aperture_size = 3;
    bool do_merge = false;
    cv::Ptr<cv::ximgproc::FastLineDetector> fld = cv::ximgproc::createFastLineDetector(length_threshold,
                                                                                              distance_threshold,
                                                                                              canny_th1, canny_th2,
                                                                                              canny_aperture_size,
                                                                                              do_merge);
    vector<cv::Vec4f> lines_fld;
    // Because of some CPU's power strategy, it seems that the first running of
    // an algorithm takes much longer. So here we run the algorithm 10 times
    // to see the algorithm's processing time with sufficiently warmed-up
    // CPU performance.
    for (int run_count = 0; run_count < 10; run_count++) {
        double freq = cv::getTickFrequency();
        lines_fld.clear();
        int64 start = cv::getTickCount();
        // Detect the lines with FLD
        fld->detect(image_gray, lines_fld);
        double duration_ms = double(cv::getTickCount() - start) * 1000 / freq;
        cout << "Elapsed time for FLD " << duration_ms << " ms." << endl;
    }

    // Show found lines with FLD
    cv::Mat line_image_fld(image_gray);
    fld->drawSegments(line_image_fld, lines_fld);
    cv::imshow("FLD result", line_image_fld);

    cv::waitKey();
    return 0;
}



