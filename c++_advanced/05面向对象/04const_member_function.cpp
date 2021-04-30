#include <iostream>
using namespace std;

class Demo{
    public:
        Demo(string name,int age){
            this->name = name;
            this->age = age;
        }
        void printName(){
            cout << this->name << endl;
        }
        void printAge()const{
            cout << this->age << endl;
        }
    private:
        string name;
        int age;
};

void test(const Demo demo){ // 这里的demo 是常对象 只能调用 常函数,不能调用 普通成员函数
    //demo.printName(); // 编译失败
    demo.printAge();
}

int main(){

    Demo d("tom",18);
    test(d);

    return 0;
}

