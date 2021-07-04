#! /usr/bin/env python
# coding:utf8

import rospy
import rospkg
import yaml
import sys
import random

"""
分为两步:
    1 从param server 中读取到 target material 的索引
    2 读取配置文件,并根据索引获得物料出现的位置
"""


def load():
    # 1 读取索引
    target_idx = rospy.get_param("target_material_idx")
    if target_idx == -1:
        # 0 - 8  随机一个
        target_idx = random.randint(0, 8)
    elif target_idx < 0 or target_idx > 8:
        sys.exit(-1)

    # 2 配置文件的路径
    rp = rospkg.RosPack()
    path = rp.get_path("common_pkg") + "/config/material_locations.yaml"
    with open(path, "r") as f:
        yaml_obj = yaml.load(f)

    # 3 得到目标位置
    target_pos = yaml_obj["locations"][target_idx]
    x, y, z = target_pos

    # 4 拼造出gazebo spawn model 的参数信息,并上传到 param server
    arg = "-urdf -param material_description -model material -x %f -y %f -z %f" % (x, y, z)
    rospy.set_param("gazebo_ros_spawn_model_arg", arg)


if __name__ == '__main__':
    load()
