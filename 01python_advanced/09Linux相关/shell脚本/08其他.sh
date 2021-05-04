#! /bin/bash 
: '
# =========== 获取用户输入========
read -p "请输入名字" name # -p 是提示用户 prompt
echo $name

read -p "请输入密码" -s password # -s 隐藏用户输入的内容 safe 
echo $password


# =========== 生成一些列数字========
echo $(seq 10)
echo $(seq 3 10)
echo $(seq 1 2 10)
'

# =========== 生成 0 - 3 的随机数========
echo $(expr $RANDOM % 4)




