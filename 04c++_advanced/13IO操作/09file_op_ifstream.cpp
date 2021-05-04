#include <iostream>
#include <fstream>

using namespace std;

int main(){
    
    ifstream ifs("data.txt",ios::in); 
    if(ifs.is_open()){
        string line;

        while(getline(ifs,line)){
            cout << line<<endl;
        }
        ifs.close();
    }else{
        cout << "无法正常打开文件" <<endl; // 一般不会走到这
    }

    return 0;
}

