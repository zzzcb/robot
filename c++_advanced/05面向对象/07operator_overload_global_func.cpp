#include <iostream>
using namespace std;

class Student{
    public:
        Student(string name,int age){
            this->name = name;
            this->age = age;
        }
        void print(){
            cout << this->name<< " | " << this->age <<endl;
        }

    private:
        string name;
        int age;
        friend Student operator+(Student& stu1,Student& stu2); // 友元
};

Student operator+(Student& stu1,Student& stu2){
    return Student(stu1.name+stu2.name,stu1.age+stu2.age);
}

int main(){

    Student stu1("tom",18);
    Student stu2("jane",28);

    Student res= stu1 + stu2;
    res.print();

    return 0;
}

