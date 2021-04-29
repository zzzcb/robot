#! /bin/bash

# ================if语句======================
: '
# 单if语句
if 条件
then
  执行语句
fi
# 双if语句
if 条件
then
  执行语句
else
  执行语句2
fi
# 多if语句
if 条件
then
  执行语句
elif 条件2
then
  执行语句2
else
  执行语句3
fi

    注意：条件结尾是fi
    使用场景：启动、停止、重启服务
'
: '
money=1000000
if [ $money -gt 100000 ]
then
    echo "有钱"
elif [ $money -lt 100 ]
then
    echo "没钱"
else
    echo "一般般"
fi
'

# ==============case语句(c中的switch)=================
: '
a=A-
case $a in 
    A+)
        echo "十分优秀"
    ;;
    A|A-)
        echo "优秀"
    ;;
    B+|B|B-)
        echo "良好"
    ;;
    *)
        echo "垃圾"
    ;;
esac
'

# ==============for循环=================
#for i in `seq 10`
#for i in $(seq 10)
for i in $(seq  3 10)
do 
    echo "item -> $i"
done

: '
arr=(1 2 8 4 5)
for i in ${arr[*]};do
    echo "item -> $i"
done
'

# ==============while循环=================
: '
a=0
while [ $a -lt 10 ]
do
    echo "a : $a"
    let a=a+1
done
'

# =============无限循环==================
: '
while true
do 
    echo "hello"
done
'


