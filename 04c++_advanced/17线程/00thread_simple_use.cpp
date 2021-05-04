#include <thread>
#include <iostream>
#include <unistd.h>

using namespace std;

void show(){
    for(int i = 0 ; i < 10 ;i ++){
        cout <<__func__ << " = " << i  << endl;
        sleep(1);
    }
}


int main() {
    thread t(show) ;

    t.join();
    cout << "执行了main函数 " <<endl;

    return 0;
}

