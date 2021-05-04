#include <iostream>
using namespace std;

class Student{
    public:
        Student(){}
        Student(string name,int age){
            this->name = name;
            this->age = age;
        }

        int operator()(int val){ 

            return this->age + val;
        }

    private:
        string name;
        int age;
};

int main(){

    Student stu("tom",18);
    cout << stu(10) << endl;

    return 0;
}

