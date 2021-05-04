"""
我们除了可以使用next()函数来唤醒生成器继续执行外，还可以使用send()函数来唤醒执行。使用
send()函数的一个好处是可以在唤醒的同时向断点处传入一个附加数据。
"""

def f():
    idx = 0
    while True:
        idx += 1
        parm = yield idx 
        print("parm",parm)

if __name__ == "__main__":
    obj = f()
    print(obj.send(None)) # 第一次必须send None
    # 程序只执行到 parm = yield idx 的右面，所以parm不是None,此时获取到了 idx 

    print(obj.send("a"))
    # 程序执行 parm = yield idx 的右面, 所以这时parm是 a,并在下个循环执行到了 parm = yield idx 的右面,获取到了idx 

""" OUTPUT:
1

parm a
2
"""