# coding:utf8
import cv2 as cv
import json

if __name__ == '__main__':
    gray = cv.imread("./1.png", cv.IMREAD_GRAYSCALE)
    # cv.imshow("gray", gray)

    # 二值化
    _, bi = cv.threshold(gray, 0, 255, cv.THRESH_OTSU | cv.THRESH_BINARY_INV)
    # cv.imshow("bi", bi)

    cnt = 0
    with open("./1.pcd", "wb") as f:
        for i in range(0, bi.shape[0],3):  # 行
            for j in range(0, bi.shape[1],3):  # 列
                if bi[i][j] > 0:
                    cnt += 1
                    f.write("%f %f %f \n" % (j / 100.0, i / 100.0, 0))
    print "总数: ", cnt

    cv.waitKey()
    cv.destroyAllWindows()


