import time

# 创建生成器 work1
def work1():
    """任务1"""
    while True:
        print("正在执行work1------------")
        time.sleep(0.5)
        yield

# 创建生成器 work2
def work2():
    """任务1"""
    while True:
        print("正在执行work2----")
        time.sleep(0.5)
        yield

if __name__ == '__main__':
    # 获取生成器
    w1 = work1()
    w2 = work2()

    while True:
        # 通过生成器获取下一个值
        w1.__next__()
        w2.__next__()