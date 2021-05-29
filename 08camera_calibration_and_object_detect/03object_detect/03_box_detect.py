# coding:utf8
import cv2 as cv
import numpy as np

# def on_change(threshold):
#    global img_gray
#    cv.imshow("img_gray", img_gray)
#    ret, dst = cv.threshold(img_gray, threshold, 255, cv.THRESH_BINARY)
#    cv.imshow("dst", dst)


if __name__ == '__main__':
    img_bgr = cv.imread("images/pic9.png")
    img_bgr_copy = np.copy(img_bgr)

    cv.imshow("img_bgr_copy", img_bgr_copy)

    # 1. 去掉背景
    # 通过将图片转成HSV格式，背景的颜色值范围，筛选出背景内容 (mask中亮的部分)
    # 通过掩膜（遮罩）将原图中的背景部分去除（设置为黑色）
    img_hsv = cv.cvtColor(img_bgr_copy, cv.COLOR_BGR2HSV)
    mask = cv.inRange(img_hsv, (0, 5, 5), (88, 255, 255))  # 如果在范围 设置为 255 ，否则为 0 ，类似于二值化
    # cv.imshow("mask",mask)  # 背景色 被标为 255 了
    img_bgr_copy[mask != 0] = [0, 0, 0]  # src_copy 背景色被标为0
    cv.imshow("img_bgr_copy2", img_bgr_copy)

    # 2 形态学闭操作: 先膨胀再腐蚀
    kernel = cv.getStructuringElement(cv.MORPH_RECT, (5, 5))
    img_bgr_morph = cv.morphologyEx(img_bgr_copy, cv.MORPH_CLOSE, kernel)
    img_gray = cv.cvtColor(img_bgr_morph, cv.COLOR_BGR2GRAY)  # 转为 灰度图

    # cv.namedWindow("track_bar")
    # cv.createTrackbar("threshold", "track_bar", 0, 255, on_change)
    ret, img_bi = cv.threshold(img_gray, 10, 255, cv.THRESH_BINARY)
    cv.imshow("img_bi", img_bi)

    # 3 查找轮廓
    _, contours, hierarchy = cv.findContours(img_bi, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
    print "找到轮廓的个数: ", len(contours)
    cv.drawContours(img_bgr_copy, contours, -1, (0, 0, 255))
    cv.imshow("img_bgr_copy3", img_bgr_copy)

    # 4 多边形逼 近
    for i, contour in enumerate(contours):
        # 获取矩形区域
        x, y, w, h = cv.boundingRect(contour)

        # 计算面积
        area = cv.contourArea(contour)
        print area

        # 计算周长
        arc = cv.arcLength(contour, True)

        epsilon = arc * 0.02  # 逼近程度 阈值
        approx_curve = cv.approxPolyDP(contour, epsilon, True)
        edge_num = approx_curve.shape[0]  # 边的个数

        if area > 1000 and edge_num >= 4 and cv.isContourConvex(approx_curve):
            # 绘制
            print("hello")
            cv.rectangle(img_bgr_copy, (x, y), (x + w, y + h), (0, 255, 0))

    cv.imshow("img_bgr_copy4", img_bgr_copy)

    cv.waitKey()
    cv.destroyAllWindows()
