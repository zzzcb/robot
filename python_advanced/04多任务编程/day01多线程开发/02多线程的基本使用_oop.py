import threading,time

class MyThread(threading.Thread):
    def __init__(self):
        super().__init__()

    def run(self):
        print("thread")

if __name__=="__main__":
    thread = MyThread()
    thread.start()
    time.sleep(2)
    print("main_thread")
