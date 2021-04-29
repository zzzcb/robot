#! /bin/bash

: '
# 定义
函数名(){
    函数体 $n
}

# 调用
函数名 参数
'

func(){
    echo "hello i am func! $0 $1 $2"
    return 123
}
func 10086 中国移动
echo $?



