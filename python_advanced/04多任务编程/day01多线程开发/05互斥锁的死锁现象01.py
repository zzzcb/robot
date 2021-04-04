import threading,time

# add 100w times
def thread_a(lock):
    global num
    lock.acquire()
    lock.acquire() # 死锁 
    for i in range(1000000):
        num += 1
    lock.release()
    lock.release()

# add 100w times
def thread_b(lock):
    global num
    lock.acquire()
    for i in range(1000000):
        num += 1
    lock.release()

if __name__ == "__main__":
    num = 0 # 全局变量
    lock = threading.Lock()

    thread1 =threading.Thread(target=thread_a,args=(lock,))
    thread2 =threading.Thread(target=thread_b,args=(lock,))
    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()
    print(num)