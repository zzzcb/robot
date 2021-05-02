#include <iostream>

using namespace std;

int main (){

    bool flag = false;
    cout << "flag的值是：" << flag << endl; // 打印 0

    //操作符只会影响后续的输出  打印 0  false
    cout << "flag的值是：" << flag  <<" 添加操作符后："<<boolalpha << flag << endl;

    return 0 ;
}

