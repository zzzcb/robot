#! /bin/bash

if [ $# -lt 2 -o $# -gt 5 ];then
    echo "参数的个数只能有2-5个"
    exit
fi

for i in $*;do
    echo "args : $i"
done















