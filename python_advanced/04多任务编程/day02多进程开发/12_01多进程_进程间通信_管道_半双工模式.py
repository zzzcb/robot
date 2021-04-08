import multiprocessing
import time

def process_receiver(pipe):
    while True:
        data = pipe.recv()
        print("pipe -> recv: \33[42;1m 接收 \033[0m", data)
        pipe.send("报告:{}".format(data))

def process_sender(pipe):
    for i in range(100):
        print("send -> pipe: \33[41;1m 发送 \033[0m",i)
        pipe.send(i)
        resp = pipe.recv()
        print("收到回复-> {}".format(resp))
        time.sleep(1)

if __name__ == '__main__':
    # duplex半双工模式,默认也是它
    pipe = multiprocessing.Pipe(duplex=True)
    p_receiver = multiprocessing.Process(target=process_receiver, args=(pipe[0],))
    p_sender = multiprocessing.Process(target=process_sender, args=(pipe[1],))

    p_receiver.start()
    p_sender.start()
