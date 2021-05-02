#include <iostream>
#include <fstream>

using namespace std;

int main(){
    
    ofstream ofs("data.txt",ios::out);// 写入到 data.txt // 无则创建
                          //ios::app 追加
    if(ofs.is_open()){
        ofs << "hello world0" <<endl;
        ofs << "hello world1" <<endl;
        ofs << "hello world2" <<endl;
        ofs << "hello world3" <<endl;
        ofs.close();
    }else{
        cout << "无法正常打开文件" <<endl; // 一般不会走到这
    }

    return 0;
}

