#! /usr/bin/env python
# coding:utf8


import re
pattern = re.compile(r":| ") # 以: 或者 空格 作为delimit
ret = pattern.split("addr:Beijing tom 18")
print ret


# Python自带的 str.split() 的方法默认只能按一个delimit

