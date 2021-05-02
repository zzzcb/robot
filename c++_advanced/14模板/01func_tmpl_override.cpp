#include <iostream>
using namespace std;

template<typename T>
T add(const T&  a,const T& b){
    return a + b;
}

template<typename T>
T add(const T&  a,const T& b,const T& c){
    return a + b + c;
}

int main(){

    int res = add<int>(3,3);
    cout << res <<endl;
    res = add<int>(3,3,1);
    cout << res <<endl;


    
    double res2 = add<double>(3.333,3.323);
    cout << res2 <<endl;
    res2 = add<double>(3.333,3.323,0.555);
    cout << res2 <<endl;

    return 0;

}











