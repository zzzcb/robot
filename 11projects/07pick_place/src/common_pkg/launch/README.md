#1 
load_material.launch 的作用是读取配置文件，进行数据处理，将要生成的物料位置放入param server

spawn_material.launch 的作用是在1中物料位置处中生成该模型

注意这两个launch不能合并,spawn_material.launch 要在load_material.lauch 后执行

