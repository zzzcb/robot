"""
一个对象所属的类中含有 __iter__() 方法，该对象就是一个可迭代对象。
判断是否可迭代：通过isinstance(obj,collections.Iterable)
"""
from collections import Iterable
class MyDemo:
    def __iter__(self): 
        pass 

if __name__ == "__main__":
    obj1 = [1,2,3]
    print(isinstance(obj1,Iterable))

    obj2 = MyDemo()
    print(isinstance(obj2,Iterable))
