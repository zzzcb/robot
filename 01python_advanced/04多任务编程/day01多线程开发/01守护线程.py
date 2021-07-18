import threading,time

def thread_a():
    while True:
        time.sleep(1)
        print("thread_a")

if __name__ == "__main__":
    thread_a = threading.Thread(target=thread_a)
    thread_a.setDaemon(True) # 当main_thread代码结束时，thread_a 线程也跟着结束
    thread_a.start()
    print("main_thread")

    time.sleep(3)
