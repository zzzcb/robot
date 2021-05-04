#include <iostream>

using namespace std;

int main (){


    double a = 10.12345678901234;
    double b = 3.1415936;

    cout.precision(3); //  设置输出多少位数字 ,该函数有返回值，为设置的精度值。
    cout  <<" a ="<<a << endl;  // 10.1 
    cout  <<" b ="<<b << endl;  // 10.1 

    return 0 ;
}

