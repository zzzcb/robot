#include <iostream>
#include <sstream>

using namespace std;

int main (){

    // 字符串 输入流  
    istringstream iss; // in stream
    iss.str("hello world what fuck");

    string s;
    while (iss>>s){
        cout << s <<endl;
    }

    return 0 ;
}

