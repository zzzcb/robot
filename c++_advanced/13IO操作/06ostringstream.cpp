#include <iostream>
#include <sstream>

using namespace std;

int main (){

    // 字符串 输出流
    ostringstream oss;// out stream

    int a = 55;
    float b = 333.33333;
    oss << a << "|" << b;
    string s = oss.str();


    cout << s << endl;


    return 0 ;
}

