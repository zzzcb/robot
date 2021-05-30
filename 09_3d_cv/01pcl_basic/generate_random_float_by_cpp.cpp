//
// Created by zcb on 5/30/21.
//
#include <iostream>
#include <cstdlib>
#include <ctime>


float random_float() {
    return 1024 * rand() * 1.0 / RAND_MAX; // (-1,1) 小数
}

float random_float2() {
    return 1024.0f * rand() * 1.0 / RAND_MAX; // (0,1024) 小数  // 此时不会溢出
}
int main(){

    srand(time(NULL));

    for(int i =0;i<10;i++){
        std::cout << random_float() <<std::endl;
    }

    return 0;
}

