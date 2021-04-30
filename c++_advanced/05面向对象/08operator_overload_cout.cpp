#include <iostream>
using namespace std;

class Student{
    public:
        Student(string name,int age){
            this->name = name;
            this->age = age;
        }
    private:
        string name;
        int age;
        friend ostream& operator<<(ostream& out,Student& stu); // 友元
};

ostream& operator<<(ostream& out,Student& stu){
    out << stu.name << " | " <<stu.age ; 
    return out;
}

int main(){

    Student stu("tom",18);
    cout << stu << endl;

    return 0;
}

