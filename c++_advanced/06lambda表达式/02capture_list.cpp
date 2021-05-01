#include <iostream>
using namespace std;

int main(){

    int a = 3;
    int b = 5;
    // 值传递 a,b  ,函数体内 无法修改 a,b 的值
    //[a,b](){a = 0;b=0;}();

    // 引用传递 a,b
    [&a,&b](){a =0;b=0;}();
    cout << a << " | " << b << endl;
    

    return 0 ;
}

