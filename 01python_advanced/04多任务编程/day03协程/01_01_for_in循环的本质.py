"""
for in 循环的要求是: 对象是可迭代对象（有__iter__()），而且__iter__() 返回一个迭代器.

for val in [1,2,3]: # list 不是迭代器，但是它是一个可迭代对象，并且__iter__() 返回一个迭代器，所以可以使用for in 遍历它。
    pass 
"""
import time
class MyIterator:
    def __init__(self,l):
        self.l = l
        self.idx = 0

    def __iter__(self): # 一般返回 迭代器
        return self 

    def __next__(self): # 返回当前迭代的值 
        if self.idx >= len(self.l):
            raise StopIteration
        else:
            retVal = self.l[self.idx]
            self.idx += 1
            return retVal 

if __name__ == "__main__":
    l1 = MyIterator([1,2,3])
    for val in l1:
        print(val)
    
    # 上面三行等价于下面的代码
    l2 = MyIterator([1,2,3])
    while True:
        try:
            print(l2.__next__())
        except StopIteration:
            break

