#include <iostream>

int main(int argc , char ** args) {

    std::cout << "参数个数："<< argc << std::endl;

    if(argc >= 2){
        std::cout << "第一个参数："<< args[0] << std::endl;
        std::cout << "第一个参数："<< args[1] << std::endl;
    }else{
        std::cout << "请输入两个参数以上" << std::endl;
    }


    return 0;
}
