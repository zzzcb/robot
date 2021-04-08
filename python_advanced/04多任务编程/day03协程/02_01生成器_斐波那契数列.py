def fib(n):
    if n <= 0:
        raise Exception("n应该大于等于1") 

    a = 0
    b = 1
    idx = 0

    while True:
        if idx >= n:
            break
        else:
            idx += 1
            if idx == 1:
                yield a 
                continue
            elif idx == 2:
                yield b
                continue

            retVal = a + b 
            a,b = b,a+b
            yield retVal

if __name__ == "__main__":

    for i in range(1,11):
        obj = fib(i)
        print(f"fib({i}):",list(obj))
