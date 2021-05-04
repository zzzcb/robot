#! /usr/bin/env python
# coding:utf8

"""
match（）只有从0位置匹配成功的话才有返回，如果不是开始位置匹配成功的话，match()就返回none
search()会扫描整个string查找匹配
"""
import re

pattern = re.compile(r"(\d+)")

ret = pattern.match("阅读次数: 8888")
if ret:
    print ret.group(0)
    print ret.group(1)


print "==="
ret = pattern.search("阅读次数: 8888")
if ret:
    print ret.group(0)
    print ret.group(1)



# ===
print "==="
pattern = re.compile(r".*?(\d+)") # * 是 非贪婪 
ret = pattern.match("阅读次数: 8888")
if ret:
    print ret.group(0)
    print ret.group(1)




