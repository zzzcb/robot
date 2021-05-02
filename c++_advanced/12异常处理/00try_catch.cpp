#include <iostream>
using namespace std;

int calcDiv(int a, int b){

    if(b == 0){
        throw  runtime_error("除数不能为0 ");
    }
    return a / b;
}
int main(){

    try{
        calcDiv(3,0);
    }catch(runtime_error err){
        cout << err.what() << endl;
    }

    return 0;
}

