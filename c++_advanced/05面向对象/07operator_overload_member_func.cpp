#include <iostream>
using namespace std;

class Student{
    public:
        Student(string name,int age){
            this->name = name;
            this->age = age;
        }
        Student operator+(Student& stu){
            return Student(this->name + stu.name,this->age+stu.age);
        }
        void print(){
            cout << this->name<< " | " << this->age <<endl;
        }

    private:
        string name;
        int age;
};


int main(){

    Student stu1("tom",18);
    Student stu2("jane",28);

    Student res= stu1 + stu2;
    res.print();

    return 0;
}

