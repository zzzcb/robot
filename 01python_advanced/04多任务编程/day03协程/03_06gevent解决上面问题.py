
import gevent
import time

def work1():
    """任务1"""
    while True:
        print("正在执行work1------------")
        time.sleep(0.5) # 注意 time.sleep 不能被 gevent 识别，所以此程序运行起来只会一直执行work1

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