import threading,time

def A(lockA,lockB):
    lockA.acquire() 
    time.sleep(1)
    lockB.acquire() 

    lockB.release()
    lockA.release()

def B(lockA,lockB):
    lockB.acquire() 
    time.sleep(1)
    lockA.acquire() 

    lockA.release()
    lockB.release()

if __name__ == "__main__":
    lockA,lockB = threading.Lock(),threading.Lock()
    thread_1 = threading.Thread(target=A,args=(lockA,lockB))
    thread_2 = threading.Thread(target=B,args=(lockA,lockB))

    thread_1.start()
    thread_2.start()

    