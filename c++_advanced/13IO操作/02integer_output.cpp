#include <iostream>

using namespace std;

int main (){

    cout <<"十进制：" << dec  <<9 << endl;  // 9
    cout <<"八进制：" << oct  <<9 << endl;  // 10 
    cout <<"十六进制：" << hex <<10 << endl; // a


    //若想在输出前面表示打印的数值显示前缀进制标识，可以使用showbase关键字
    cout <<showbase;
    //默认即采用十进制输出
    cout <<"十进制：" << dec  <<9 << endl; // 9
    cout <<"八进制：" << oct  <<9 << endl; // 011
    cout <<"十六进制：" << hex <<10 << endl;  //0xa
    cout<<noshowbase;



    return 0 ;
}

