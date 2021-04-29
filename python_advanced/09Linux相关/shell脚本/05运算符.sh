#! /bin/bash


# ================算数运算符======================
: '
原生bash不支持数学运算，使用expr完成表达式的求值
注意数字和运算符之间严格要求要有空格
'
: '
ret=`expr 3 + 2`
echo "计算结果: $ret"

a=10
b=20
ret=`expr $a + $b`
echo "a+b: $ret"

ret=`expr $a - $b`
echo "a-b: $ret"

ret=`expr $a \* $b`
echo "a*b: $ret"

ret=`expr $a / $b`
echo "a/b: $ret"

ret=`expr $a % $b`
echo "a%b: $ret"
'

# ================关系运算符======================
: '
支持数字或内容是数字的字符串

如果希望直接使用>或<等符号,需要在数值操作符(())中使用
'
: '
a=10
b=20
[ $a -eq $b ]
echo $?

[ $a -ne $b ]
echo $?


[ $a -gt $b ]
echo $?

[ $a -lt $b ]
echo $?

[ $a -ge $b ]
echo $?

[ $a -le $b ]
echo $?

echo "============"

(( $a > $b ))
echo $?
(( $a >= $b ))
echo $?
(( $a < $b ))
echo $?
(( $a <= $b ))
echo $?
(( $a == $b ))
echo $?
(( $a != $b ))
echo $?
'
# ================逻辑运算符======================
# -a &&  :与 and
# -o ||  :或 or 
: '
a=10
b=20
[ $a -gt 10 -a $b -gt 15 ]
echo $?

[ $a -gt 10 -o $b -gt 15 ]
echo $?

[[ $a -gt 10 && $b -gt 15 ]]
echo $?

[[ $a -gt 10 || $b -gt 15 ]]
echo $?

[ $b -gt 15 ] && echo "b 大于 15"
'

# ================文件运算符======================
: '
-f 判断输入内容是否是文件
-d 判断输入内容是否是目录
-x 判断输入内容是否有执行权限
-e 判断输入的文件或文件夹是否存在 
'
: '
[ -f test.sh ] && echo "test.sh是一个文件"
[ -d test.sh ] && echo "是一个文件夹"
[ -x test.sh ] && echo "有执行权限"
[ -e test.sh ] && echo "存在test.sh"
'


# ================字符串运算符======================
: '
a=hello
b=world

[ $a == $b ]
echo $?

[ $a != $b ]
echo $?

[ -z $a ] # 字符串长度是否为0  zero
echo $?

[ -n $a ] # 字符串长度是否不为0 not zero
echo $?

[ $a ]  # 字符串是否 非空 
echo $?
'

