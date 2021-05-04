#! /bin/bash


for i in $(seq 9);do
    for j in $(seq $i);do
        echo -n "$i*$j =  $((i*j))  " # -n  不换行 nowrap
    done
    echo "" # 换行
done

