#! /bin/bash
# 参考 http://robot.czxy.com/docs/linux/chapter02/06-shell-task-cron/#linuxcron
: '
    定时备份 ~/github(提前创建) 为 日期.tar.gz 并存放在 ~/bak 目录(提前创建)
    删除5分钟之前的备份文件
    在cron 的文件中加入下面命令即可:
        */15 * * * * bash xxx.sh >> /tmp/bakeup.log # 每隔15 min执行 xxx.sh 脚本一次
'

date_time=$(date +'%Y%m%d%H%M%S%s')
tar -zcf ~/bak/"${date_time}.tar.gz" ~/github # zcvf v 是输出 

find ~/bak -name "*.tar.gz" -mmin +5 | xargs rm -f


