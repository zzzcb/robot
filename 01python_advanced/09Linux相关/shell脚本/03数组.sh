#! /bin/bash

arr=(A B C D)
# 获取指定的元素
echo "元素0 :"${arr[0]}
echo "元素3 :"${arr[3]}

# 获取所有元素 及 长度 
echo "数组的所有的元素:${arr[*]} 长度: ${#arr[*]}"
echo "数组的所有的元素:${arr[@]} 长度: ${#arr[@]}"

# 添加元素
arr+=(1)
echo "${arr[*]}"


# 删除元素
unset arr[3]
echo "${arr[*]}"

# 清空数组 
unset arr
echo "${arr[*]}"


