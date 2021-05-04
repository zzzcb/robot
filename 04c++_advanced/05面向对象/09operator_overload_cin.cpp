#include <iostream>
using namespace std;

class Student{
    public:
        Student(string name,int age){
            this->name = name;
            this->age = age;
        }
        void print(){
            cout << this->name << " | " << this-> age <<endl;
        }

    private:
        string name;
        int age;
        friend istream& operator>>(istream& in,Student& stu); // 友元
};

istream& operator>>(istream& in,Student& stu){
    in >> stu.name >> stu.age; 
                                // 相当于 in >> stu.name;  // 空格,换行分割都可以
                                        //in >> stu.age;
    return in;
}

int main(){

    Student stu("tom",18);
    stu.print();
    cin >> stu;
    stu.print();

    return 0;
}

