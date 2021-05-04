#! /bin/bash
: '
    备份 ~/github(提前创建) 为 日期.tar.gz 并存放在 ~/bak 目录(提前创建)
    删除5分钟之前的备份文件
'

date_time=$(date +'%Y%m%d%H%M%S%s')
tar -zcf ~/bak/"${date_time}.tar.gz" ~/github # zcvf v 是输出 

find ~/bak -name "*.tar.gz" -mmin +5 | xargs rm -f


