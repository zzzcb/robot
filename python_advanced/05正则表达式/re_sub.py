#! /usr/bin/env python
# coding:utf8

"""
要求： 从 data.html 中提取文本
"""
import re
with open("data.html","r") as f:
    html  = f.read()
    pattern = re.compile(r"<.*?>|&nbsp;")
    ret = pattern.sub("",html)
    print ret

