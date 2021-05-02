#include <thread>
#include <iostream>
#include <unistd.h> // for sleep

using namespace std;

void show(string name){
    for(int i = 0 ; i < 10 ;i ++){
        cout <<__func__ << " = " << i<<name  << endl;
        sleep(1);
    }
}


int main() {
    thread t(show,"tom") ;

    t.join();
    cout << "执行了main函数 " <<endl;

    return 0;
}

