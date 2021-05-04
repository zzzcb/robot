import threading,time

def A(lock):
    lock.acquire() 
    time.sleep(1)
    lock.acquire() 

    lock.release()
    lock.release()

def B(lock):
    lock.acquire() 
    time.sleep(1)
    lock.acquire() 

    lock.release()
    lock.release()

if __name__ == "__main__":
    lock = threading.RLock()
    thread_1 = threading.Thread(target=A,args=(lock,))
    thread_2 = threading.Thread(target=B,args=(lock,))

    thread_1.start()
    thread_2.start()

    