#include <iostream>

using namespace std;

class Father{

    string name;
public:
    Father(string name):name(name){
        cout << "执行父亲构造函数" <<endl;
    }
};



class Mother{
    int age;

public:
    Mother(int age):age(age){
        cout << "执行母亲构造函数" <<endl;
    }

};
class Son:public Father , public Mother{

public:
    Son(string name ,int age):Father(name),Mother(age){
        cout << "执行孩子构造函数" <<endl;
    }
};

int main(){

    Son s("无名氏" ,38);

    return 0 ;
}

