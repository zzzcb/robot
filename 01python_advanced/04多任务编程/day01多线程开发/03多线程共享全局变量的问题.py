import threading,time

# add 100w times
def thread_a():
    global num
    for i in range(1000000):
        num += 1

# add 100w times
def thread_b():
    global num
    for i in range(1000000):
        num += 1

if __name__ == "__main__":
    num = 0 # 全局变量
    thread1 =threading.Thread(target=thread_a)
    thread2 =threading.Thread(target=thread_b)
    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()
    print(num)

















