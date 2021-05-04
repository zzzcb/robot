#include <iostream>
#include <string>

using namespace std;

class Student{

    public:
        Student(string name , int age,int*scores,int num):name(name),age(age),scores(scores),num(num){
        }

    public :
        string name;
        int age ;
        int* scores; // int scores[num]
        int num;
};

int main(){

    int scores[3] = {100,80,90};
    Student s1("张三", 19,scores,3);


    cout << s1.name << " | " << s1.age<< " | "<< s1.scores[0] <<endl;
    cout << &s1.name << " | " << &s1.age<< " | "<<s1.scores <<endl;

    cout <<"===============" << endl;

    Student s2 = s1;

    cout << s2.name << " | " << s2.age<< " | "<< s2.scores[0] <<endl;
    cout << &s2.name << " | " << &s2.age<< " | "<<s2.scores <<endl;



    cout <<"===============" << endl;
    s1.scores[0] = 200;
    cout <<"s1.scores[0] " << s1.scores[0] << " s2.scores[0] " << s2.scores[0] << endl;


    return 0 ;
}




