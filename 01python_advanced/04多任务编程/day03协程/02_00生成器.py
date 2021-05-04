"""
生成器是特殊的迭代器,
特殊的地方在于，我们可以通过两种语法方式快速的创建。
1,通过 ()  
2,通过函数中使用yield  
"""

from collections import Iterator

obj = (x for x in range(10))
print(obj)

obj = (x for x in range(10))
print(isinstance(obj,Iterator))


def func():
    while True:
        print("hello")
        yield 1
obj = func()
print(obj)
print(isinstance(obj,Iterator))
