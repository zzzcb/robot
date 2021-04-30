#include <iostream>
using namespace std;

class Demo{
    public:
        Demo(string name,int age){
            this->name = name;
            this->age = age;
        }

        static string school; // 所有的对象 都公用这一个属性
        static void printHello(){ // 静态成员函数 ,里面只能访问 静态成员变量 
            cout << "hello"<<endl;
        }

    private:
        string name;
        int age;
};

string Demo::school = "NCHU";

int main(){

    Demo d("tom",18);
    cout << d.school<<endl;

    Demo::printHello();


    return 0;
}

