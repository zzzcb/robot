"""
生成器代码中使用return 关键字，语法上没有问题
但是如果执行到 return 语句以后，生成器会停止迭代，抛出StopIteration,
"""


def f():
    idx = 0
    while True:
        if idx == 3:
            return idx

        idx += 1
        yield idx
if __name__ == "__main__":
    obj = f()
    for i in obj:
        print(i)

    try:
        obj = f()
        print(obj.__next__())
        print(obj.__next__())
        print(obj.__next__())
        print(obj.__next__())
    except StopIteration as e:
        print("-->",e.value) # e.value 是return 后面的值