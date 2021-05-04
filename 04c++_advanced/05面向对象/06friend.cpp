#include <iostream>
using namespace std;

class Demo{
    public:
        Demo(string name,int age){
            this->name = name;
            this->age = age;
        }

    private:
        string name;
        int age;
        friend void test(Demo& d);//声明 test 为友元函数 
        friend class HHHHH; // 声明 HHHHH 为 友元类 HHHHH 中的所有成员函数就都可以访问了 
};

class HHHHH{
    public:
        void print01(Demo& d){
            d.name = "shit";
            cout << d.name << endl;
        }

        void print02(Demo& d){
            d.age = 20;
            cout << d.age << endl;
        }
};

void test(Demo& d){
    d.name = "fuck";
    cout << d.name <<endl;
}

int main(){

    Demo d("tom",18);
    test(d);

    HHHHH h;
    h.print01(d);
    h.print02(d);


    return 0;
}

