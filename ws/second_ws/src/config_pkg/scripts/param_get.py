#! /usr/bin/env python
# coding:utf8

import rospy

if __name__ == '__main__':
    nodeName = "param_get_node"
    rospy.init_node(nodeName)

    # python 很简单，如果又key1 就返回其对应的值，不然返回10 ，不区分类型
    ret = rospy.get_param("key1", 10)
    print(ret)
