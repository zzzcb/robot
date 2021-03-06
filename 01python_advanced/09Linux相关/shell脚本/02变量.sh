#! /bin/bash
: '
变量的分类:
    1. 本地变量:本地有效
    2. 全局变量:当前系统，所有环境都有效
    3. 内置变量:bash中默认包含的变量，可以直接使用


'
###########################本地变量###################################
#普通变量 
: '
变量名=变量值：变量值必须是一个整体，中间不能有特殊字符
变量名='变量值'：看到的内容和输出的内容一致
变量名="变量值 "：如果在变量A的变量值范围内，有可以解析的变量B，那么就首先解析变量B，将B的结果和其他内容组合后，再赋值给A eg.
'

: '
a=123
b="zcb"
c="->$a"
d="->$b"

e='->$b'
echo $a
echo $b
echo $c
echo $d
echo $e
'


#命令变量 
: '
变量名=`命令`
变量名=$(命令)
'
: '
a=`whoami`
echo "现在登录的用户名字是: $a"

echo "现在登录的用户名字是: $(whoami)"
echo "bash 的路径在: $(which bash)"
'

###########################全局变量###################################
# export 是 设置进 env 环境变量

# 当前会话的全局变量 export 将会设置进当前会话的env
: '
    1.首先定义一个本地变量
    2.然后,使用export声明这个本地变量为全局变量
'
: '
tom="helloworld"
export tom

# or 
export tom2="helloworld2"
echo "========================================"
env | grep tom
echo "========================================"
env | grep tom2
'


: '
如果export在一个文件中，则需要使用source filename.sh使其生效
删除变量：
unset 变量名
'

# 当前用户的全局变量
# 写入到 ~/.bashrc 添加 
# 例如 export tom=10086 # 将会设置进 当前用户的env 


###########################内置变量###################################
: '
查看bash内置变量：man bash

    与脚本文件有关系的变量
        $0 获取脚本的名称
        $# 获取脚本的参数数量
        $n 获取指定位置的参数
        $* 所有的参数
        $? 获取上一个命令执行的返回值

    字符串相关的内置变量
        从索引3取5位：echo ${str:3:5}
'
: '
echo $0
echo $#
echo $2
echo $*
echo $?
'
: '
s="0123456789"
echo ${s:3:5} # from 3 ,get 5 
echo ${s:0:-2} # from 0 ,to -2 

echo ${s: -2}  # 倒数 2个 奇怪的写法,与上面不一致 -2 不是索引
'







###########################变量的默认值###################################
#变量为null 或 空字符串的时候: 默认值：${变量名:-默认值}
a=123
echo "a:${a:-666}"
echo "b:${b:-888}"

