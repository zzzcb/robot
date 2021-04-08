"""
如果一个对象是可迭代对象，并且它又实现了 __next__() 方法，那么这个对象就是迭代器.
判断是否可迭代：通过isinstance(obj,collections.Iterator)
"""
from collections import Iterator
class MyDemo01:
    def __iter__(self):
        pass 

class MyDemo02:
    def __next__(self):
        pass 

class MyDemo03:
    def __iter__(self): 
        pass 
    def __next__(self):
        pass 

if __name__ == "__main__":
    obj1 = [1,2,3]
    print(isinstance(obj1,Iterator))

    obj2 = MyDemo01()
    print(isinstance(obj2,Iterator))

    obj3 = MyDemo02()
    print(isinstance(obj3,Iterator))

    obj4 = MyDemo03()
    print(isinstance(obj4,Iterator))
