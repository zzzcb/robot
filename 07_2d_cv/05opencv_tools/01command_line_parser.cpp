//
// Created by zcb on 5/16/21.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void print_help() {
    cout << "进行相机标定" << endl;
    cout << "参数说明: " << endl;
    cout << "  <w>: board corner point width" << endl;
    cout << "  <h>: board corner point height" << endl;
    cout << "  <square_size>: board square size,default is 20mm" << endl;
    cout << "  <cnt>: 收集图片的数量,default is 15" << endl;
    cout << "  -flip:水平反转图片" << endl;
    cout << "  -h --help:帮助" << endl;
}

int main(int argc, char **argv) {
    cv::CommandLineParser parser(argc, argv,
                                 "{@w||}{@h||}{@square_size|20|}{@cnt|15|image's number}{flip||是否反转图片}{help h||}");

    if (parser.has("h")) {
        print_help();
        return 0;
    }
    if (parser.has("flip")) {
        cout << "filp" << endl;
    }


    int w = parser.get<int>(0); // 角点的 大小
    int h = parser.get<int>(1); // 角点的 大小
    float square_size = parser.get<float>(2); // 单个 格子的大小
    int cnt = parser.get<int>(3); //要收集图片的数量

    cout << w << endl;
    cout << h << endl;
    cout << square_size << endl;
    cout << cnt << endl;


    return 0;
}

