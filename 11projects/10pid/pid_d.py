#! /usr/bin/env python3
# coding:utf8

import matplotlib.pyplot as plt
import sys


sv = 25
pv = 37
kd = eval(sys.argv[1]) # 0.01
pre_err = 0

pxs = [0]
pys = [pv]

for i in range(1, 11):
    err = sv - pv
    pv += kd * (err - pre_err)
    pre_err = err

    pxs.append(i)
    pys.append(pv)

plt.scatter(pxs, pys)
plt.hlines(25, 0, 10)
plt.title(f"d:{kd}")
plt.show()
