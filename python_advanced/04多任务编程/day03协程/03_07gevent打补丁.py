"""
现在有个问题，如果我们以前的代码中大量使用了 time.sleep() 等耗时方法，如果全部改
为 gevent.sleep()，工作量会比较大。
为了让程序更好的兼容 time.sleep() 我们可以给程序打补丁，以实现兼容!

关于猴子补丁为啥叫猴子补丁，据说是这样子的：
这个叫法起源于Zope框架，大家在修正Zope的Bug的时候经常在程序后面追加更新部分，这
些被称作是“杂牌军补丁(guerilla patch)”，后来guerilla就渐渐的写成了gorllia((猩猩)，再后来
就写了monkey(猴子)，所以猴子补丁的叫法是这么莫名其妙的得来的。
猴子补丁主要有以下几个用处：
1. 在运行时替换方法、属性等
2. 在不修改第三方代码的情况下增加原来不支持的功能
3. 在运行时为内存中的对象增加patch而不是在磁盘的源代码中增加

具体打补丁的方法是：
from gevent import monkey
monkey.patch_all()  # 此时，什么 time.sleep ,request,socket等等IO都会被gevent 识别了
"""
import gevent
from gevent import monkey
monkey.patch_all()
import time
def work1():
    """任务1"""
    while True:
        print("正在执行work1------------")
        time.sleep(0.5)

def work2():
    """任务1"""
    while True:
        print("正在执行work2----")
        time.sleep(0.5)

if __name__ == "__main__":
    g1 = gevent.spawn(work1) 
    g2 = gevent.spawn(work2) 

    # 等待协程执行
    g1.join()
    g2.join()
    print("执行完毕")