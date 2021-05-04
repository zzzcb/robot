#include <iostream>
using namespace std;

class Student{
    public:
        Student(){}
        Student(string name,int age){
            this->name = name;
            this->age = age;
        }

        Student operator=(const Student& stu){ 

            this->name = stu.name +"_zcb";
            this->age = stu.age;

            return *this;
        }

        void print(){
            cout << this->name << " | " << this-> age <<endl;
        }

    private:
        string name;
        int age;
};

int main(){

    Student stu("tom",18);
    Student stu2;
    stu2 = stu;

    stu.print();
    stu2.print();

    return 0;
}

