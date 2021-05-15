# coding:utf8
import cv2 as cv
import numpy as np


# 1. 加载相机内参矩阵，畸变系数
# 2. 加载图片
# 3. 查找每个图片的角点
# 4. 查找角点亚像素
# 5. 计算对象姿态solvePnpRansac  ,位置估计
# 6. 投影3D点到图像平面  , 3d 重建
# 7. 在图片上坐标系并显示图片


def get_obj_points():
    ret = []
    for i in range(9):
        for j in range(6):
            ret.append([j, i, 0])
    return np.array(ret, np.float)


def draw(img, corners, imgpts):  # imgpts 的维度是 3
    imgpts = np.int32(imgpts).reshape(-1, 2)  # 维度 变为 2

    # 将地板绘制成绿色，参数2为多个轮廓的列表，故需要多套一层[]
    img = cv.drawContours(img, [imgpts[:4]], -1, (0, 255, 0), -1)

    print("-------------------")
    # 柱子绘制成蓝色, 参数必须是tuple类型
    for i, j in zip(range(4), range(4, 8)):
        print("{}.{} -> {}.{}".format(i, tuple(imgpts[i]), j, tuple(imgpts[j])))
        img = cv.line(img, tuple(imgpts[i]), tuple(imgpts[j]), (255, 0, 0), 3)

    # 顶部框用红色
    img = cv.drawContours(img, [imgpts[4:]], -1, (0, 0, 255), 3)

    return img


if __name__ == '__main__':
    fs = cv.FileStorage("./01calibration_chessboard.xml", cv.FILE_STORAGE_READ)
    camera_matrix = fs.getNode("camera_matrix").mat()
    dist_coeffs = fs.getNode("dist_coeffs").mat()
    fs.release()
    # print(camera_matrix)
    # print(dist_coeffs)

    capture = cv.VideoCapture(0)
    if not capture.isOpened():
        print("打开摄像头失败")
    else:
        criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)

        patternSize = (6, 9)
        obj_points = get_obj_points()

        # 3D 世界中的点 单位是 几个格子
        # axis = np.float32([[3, 0, 0], [0, 3, 0], [0, 0, -3]]).reshape(-1, 3)
        axis = np.float32([[0, 0, 0], [0, 3, 0], [3, 3, 0], [3, 0, 0],
                           [0, 0, -3], [0, 3, -3], [3, 3, -3], [3, 0, -3]])

        while True:
            isOk, frame = capture.read()
            if isOk:
                img = cv.flip(frame, 1)  # 水平反转
                img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

                # 查找角点
                is_found, corners = cv.findChessboardCorners(img_gray, patternSize, None,
                                                             cv.CALIB_CB_ADAPTIVE_THRESH + cv.CALIB_CB_FAST_CHECK + cv.CALIB_CB_NORMALIZE_IMAGE)
                if is_found:
                    corners2 = cv.cornerSubPix(img_gray, corners, (5, 5), (-1, -1), criteria)  # 亚像素 优化角点位置

                    # cv.drawChessboardCorners(img, patternSize, corners2, True)
                    # 查找旋转向量和平移向量
                    retval, rvecs, tvecs, inliers = cv.solvePnPRansac(obj_points, corners2, camera_matrix, dist_coeffs)

                    # 将3D点投影到图像平面 imgpts 为axis（3d） 在像素坐标系下的对应点
                    imgpts, jac = cv.projectPoints(axis, rvecs, tvecs, camera_matrix, dist_coeffs) # 位置估计 

                    img = draw(img, corners2, imgpts) # 3d 重建

                cv.imshow("frame", frame)
                cv.imshow("img", img)
            else:
                continue

            key = cv.waitKey(30) & 0xFF
            if key == 27:  # ESC 键
                break

        cv.destroyAllWindows()
