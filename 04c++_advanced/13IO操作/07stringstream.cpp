#include <iostream>
#include <sstream>

using namespace std;

int main (){

    stringstream ss;
    string a = "100";
    ss << a;
    int b;
    ss >> b;  // 最终效果相当于 进行了类型转换 
    if(b == 100){
        cout << "hello"<<endl; 
    }


    return 0 ;
}

