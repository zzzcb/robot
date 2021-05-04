#include <iostream>
/*

命名空间可作为附加信息来区分不同库中相同名称的函数、类、变量等。
*/
namespace zcb{
    std::string name="hello";
}
namespace fuck{
    std::string name="world";
    std::string name2="world2";
    std::string name3="world3";
    std::string name4="world4";
    std::string name5="world5";
}

// using namespace fuck; 
// using namespace这个指令会告诉编译器，后续的代码将使用指定的命名空间中的名称。 但是一般不使用 using ，防止冲突

int main(int argc , char ** args) {

    std::cout << zcb::name<< std::endl;
    std::cout << fuck::name<< std::endl;

    return 0;
}
