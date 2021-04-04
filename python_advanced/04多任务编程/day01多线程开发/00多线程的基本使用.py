import threading,time 

def thread_a():
    print("thread_a")

def thread_b():
    print(threading.enumerate())
    print("thread_b")

if __name__ == "__main__":
    thread_a = threading.Thread(target=thread_a,name="thread_a")
    thread_b = threading.Thread(target=thread_b,name="thread_b")

    thread_a.start()
    thread_b.start()
    print("main thread")





