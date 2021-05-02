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
    cout << "子线程的id" << t.get_id() << endl;

    t.join();
    cout << "执行了main函数,主线程id: "<< this_thread::get_id() <<endl;

    return 0;
}

