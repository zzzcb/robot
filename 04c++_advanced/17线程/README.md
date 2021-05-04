## http://robot.czxy.com/docs/cpp/day09/01_thread/#_1

    线程是操作系统能够进行运算调度的最小单位。它被包含在进程之中，是进程中的实际运作单位。一条线程指的是进程中一个单一顺序的控制流，一个进程中可以并行多个线程，每条线程并行执行不同的任务

    要想使用线程，需要导入头文件#include<thread> ,并且线程并不是linux默认的库，所以需要在cmakelist里面添加这行代码 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


