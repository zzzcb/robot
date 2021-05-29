# coding:utf8
import cv2 as cv
import numpy as np

if __name__ == '__main__':
    # 1 读取图片
    src = cv.imread("./images/pic9.png")  # 牙膏
    src_bak = np.copy(src)
    cv.imshow("src", src)
    # cv.imshow("src_bak", src_bak)

    # 2 图片处理 (去掉细节 保留边缘)
    # 形态学闭操作(先膨胀,再腐蚀).去掉内部的黑点
    ret2 = cv.morphologyEx(src_bak, cv.MORPH_CLOSE, cv.getStructuringElement(cv.MORPH_RECT, (5, 5)))
    # cv.imshow("ret2", ret2)

    # 3 提取边缘 (canny 边缘检测)
    ret3 = cv.Canny(ret2, 100, 255)
    # cv.imshow("ret3", ret3)

    # 4 保留感兴趣的地方 ROI
    h, w = ret3.shape
    roi = np.array([
        [200, 20], [600, 20],
        [600, 320], [200, 320],
    ], dtype=np.int32)

    roi_mask = np.zeros([h, w], np.uint8)
    cv.fillPoly(roi_mask, [roi], 255)
    # cv.imshow("roi_mask", roi_mask)
    ret4 = cv.bitwise_and(ret3, roi_mask)
    cv.imshow("ret4", ret4)

    # 5 霍夫直线检测
    lines = cv.HoughLinesP(ret4, 1, np.pi / 180, 20, minLineLength=20, maxLineGap=10)
    for line in lines:
        x1, y1, x2, y2 = line[0]
        cv.line(src_bak, (x1, y1), (x2, y2), (0, 0, 255), 5)
    cv.imshow("src_bak", src_bak)

    cv.waitKey(0)
    cv.destroyAllWindows()
