#include <iostream>
using namespace std;

int main(){
    //1. 使用变量接收，然后再调用 
    auto f = [](int a ,int b)->int{return a + b ;}; 
    int result = f(3,4); 
    cout << "result = " << result << endl;


    //2. 直接调用 
    int res =  [](int a,int b)->int{return a+b;}(1,2);
    cout << "res = " << res << endl;



    return 0 ;
}

