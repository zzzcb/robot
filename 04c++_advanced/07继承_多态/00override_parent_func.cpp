#include <iostream>

using namespace std;

class WashMachine{
public:
    WashMachine(string name):name(name){
    }
    void wash(string yf){
        cout << "洗衣机 "+this->name+" 在洗 "+yf << endl;
    }
private:
    string name;
};


class SmartWashMachine : public WashMachine{
public:
    SmartWashMachine(string name):WashMachine(name){
    }
    void wash(string yf){

        WashMachine::wash(yf); // 调用父类 方法 
        cout << "新升级，更省电~" << endl;
    }
};

int main(){

    SmartWashMachine s("小天鹅");
    s.wash("衬衫");

    return 0 ;
}


















