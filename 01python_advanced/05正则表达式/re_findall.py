#! /usr/bin/env python
# coding:utf8


import re
pattern = re.compile(r"\d+")
ret = pattern.findall("阅读次数:8888,评论次数:2222,转发次数:888")
print ret


