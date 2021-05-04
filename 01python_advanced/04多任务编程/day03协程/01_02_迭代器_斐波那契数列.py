class Fib:
    def __init__(self,n):
        self.n = n
        self.idx = 0

        self.a = 0
        self.b = 1
        if self.n <= 0:
            raise Exception("n 应该大于等于1")

    def __iter__(self): # 一般返回 迭代器
        return self 

    def __next__(self): # 返回当前迭代的值 
        if self.idx >= self.n:
            raise StopIteration
        else:
            self.idx += 1

            if self.idx == 1:
                return self.a
            elif self.idx == 2:
                return self.b

            retVal = self.a + self.b 
            self.a,self.b = self.b,self.a +self.b
            return retVal

if __name__ == "__main__":
    for i in range(1,11):
        fib = Fib(i)
        print(f"Fib({i})",list(fib))
   