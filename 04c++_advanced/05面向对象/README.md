# http://robot.czxy.com/docs/cpp/day04/01_class_object/#_1

## class 


## struct 
struct 和 class 一样，只不过struct内的成员默认是 public

## 在栈中创建的对象会自动释放 



## 在堆中创建的对象需要 delete 


## 类中实现成员函数，类外实现成员函数 


## 特殊的成员函数 
构造函数
拷贝构造函数,默认是浅拷贝,
    如果要修改为 深拷贝，就要重写拷贝构造函数
    拷贝构造的参数为 const &,
    (别忘了析构自己释放,还要注意 delete只能释放堆，不能释放栈,最好统一使用,要用堆就都用堆) 

析构函数
    


移动构造函数(了解即可)
    有时候我们需要新创建的对象，拥有旧对象一模一样的数据，当然这可以使用拷贝操作来完成。
    但是假设旧对象不再使用，那么拷贝操作就显得有点弱，因为旧对象仍然占据着空间。
    C++11中推出了 移动构造操作，也就是完全的把旧对象的数据 "移动" 到新对象里面去，并且把旧对象被清空了。
    右值引用一般用于绑定到一个即将销毁的对象，所以右值引用又通常出现在移动构造函数中。


## 常函数 const memeber function
    在编写代码的时候，如果确定了某个成员函数不会修改成员变量，那么可以把该函数声明为常函数。
    常函数其实也是函数，它浓缩了函数和常 这个概念在里面，函数体内不允许修改成员变量，
    除非该成员变量使用mutable修饰
    其实 const 的本质是 const *类 this;即该 this 指向的是常量 

    void printStudent() const{ // 在成员函数后 加 const 就变成了 常函数  
    
    }


## 常对象 const object
    常对象其实也就是一个变量，和以前的常量没有相差多少。
    只不过常对象只能调用常函数，不能调用普通成员函数

    const Student s1("zhangsan " ,18); // s1 就是常对象  

## 静态成员  
    1. 静态成员变量
    2. 静态成员函数
    静态成员被类的所有对象所共享，
    成员不能在类中定义的时候初始化，但是可以在类的外部通过使用范围解析运算符 :: 来重新声明静态变量从而对它进行初始化


## 友元 
    在类的外部无法访问类的私有成员，但是有时候需要它，那么可以借助友元函数 来实现。友元函数是一种特权函数，C++允许它访问私有成员。程序员可以把一个全局函数、成员函数、甚至整个类声明为友元

    1. 友元函数
    2. 友元类 ,该类中的所有成员函数就都可以访问了


## 运算符重载 
    函数可以重载， 运算符也是可以重载的。 
    运算符重载是对已有的运算符重新进行定义，赋予其另一种功能，以达到适应不同的数据类型。
    运算符重载只是一种 “语法上的方便” ， 背后实际上是一种函数调用的方式。
    实现方式:
        1. 类中成员函数的方式
        2. 全局函数的方式


## 输出运算符重载 
    cout <<

    输出运算符重载，实际上就是 << 的重载。
    cout 其实是ostream 的一个实例，而ostream 是 类basic_ostream的一个别名。
    之所以能使用cout << 来输出内容，全是因为 basic_ostream里面对 << 运算符进行了重载.
    由于ostream 是 系统已经提供好的，所以后期我们可以使用 全局函数的方式 进行实现

## 输入运算符重载 
    cin  >>

    类似与 输出与运算符重载 


## 赋值运算符重载 
    assign =


## 调用运算符重载 
    call ()

    在标准库中定义了一组算术运算符 、关系运算符、逻辑运算符的类，每个类都有自己重载的调用运算符。要想使用这些类，需要导入 #include ， 后面要说的 lambda表达式 正是一个函数对象
    #include<functional>
    int main(){

        plus<int > p; //加法操作
        int a = p(3 , 5); // 重载  p()

        negate<int> n; //可以区绝对值
        cout <<n(-10) << endl; // 重载 n()
        return 0 ;
    }
        













