#include <iostream>
#include <set>
using namespace std;

int main(){

    //创建空白set容器
   // set<int>s ;

    //创建容器并初始化，可变参数往里面赋值，但是这里添加了重复的3. 后面的3不会被添加进去。
    set<int> s = {3,4,5,6,3};

    s.insert(16);
    s.insert({7,8,9,10}); //也可以接收多个参数

    // 删除 .erase
    s.erase(8);

    // 遍历 
    for(auto i =s.begin();i!=s.end();i++ ){
        cout << *i<<endl;
    }

    // 容量查询(是否为空，大小)
    cout << s.empty() << endl;
    cout << s.size() << endl;


    return 0 ;
}

