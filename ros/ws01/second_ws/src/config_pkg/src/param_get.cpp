//
// Created by zcb on 4/14/21.
//

#include <iostream>
#include <ros/ros.h>

using namespace std;

int main(int argc, char **argv) {

    string nodeName = "param_get_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle node;

    //string name;
    //if(node.getParam("key1",name)){ // 没有默认值，不经常使用
    //    // 取到了值 并放在 name 中
    //    cout << name <<endl;
    //} else{
    //    // 没有取到值
    //    cout << "没有取到值" << endl;
    //}

    string name;
    string default_name = "xxx";
    node.param("key1", name, default_name); // 经常用
    cout << name << endl; // 如果取到key1会将取到的值放到 name中，不然会将默认值xxx放入name


    // 注意 ： rosparam set /key1 "123" 是字符串
    //        rosparam set /key1 123 是数字 二者如果不匹配也是取不到的


    ros::spin();
}






