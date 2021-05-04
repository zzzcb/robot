"""
主要是下面四个方法
threading.Event().clear #将flag设置为“False”
threading.Event().set #将flag设置为“True”
threading.Event().is_set # 判断是否设置了flag
threading.Event().wait #会一直监听flag，如果没有检测到flag就一直处于阻塞状态
"""

import threading,time

def lighter(evt):
    # 5s 绿灯  3s红灯
    # green:  0-5      8-13      16-21
    # red  :       5-8       13-16
    cnt = 0 
    color = ""
    while True:
        if cnt % 8 == 0:
            color = "绿灯"
            evt.set() 
        elif (cnt - 5) % 8 == 0:
            color = "红灯"
            evt.clear()
        print("灯是",color)


        cnt+=1
        time.sleep(1)




def car(evt):
    while True:
        if evt.is_set():
            print("小车在动",time.time())
        else:
            print("小车等红灯中",time.time())
            evt.wait() # 阻塞该线程
            print("小车可以走了",time.time())

        time.sleep(1)

if __name__ == "__main__":
    evt = threading.Event()
    thread1 = threading.Thread(target=lighter,args=(evt,))
    thread2 = threading.Thread(target=car,args=(evt,))
    thread1.start()
    thread2.start()

""" OUTPUT:
灯是 绿灯
小车在动 1617530419.7459018
灯是 绿灯
小车在动 1617530420.7466078
灯是 绿灯
小车在动 1617530421.747452
灯是 绿灯
小车在动 1617530422.7487504
灯是 绿灯
小车在动 1617530423.7491114
灯是 红灯
小车等红灯中 1617530424.7495334
灯是 红灯
灯是 红灯
灯是 绿灯
小车可以走了 1617530427.750903
灯是 绿灯
小车在动 1617530428.752571
小车在动 1617530429.7531714
灯是 绿灯
小车在动 1617530430.753817
灯是 绿灯
小车在动 1617530431.754307
灯是 绿灯
小车在动 1617530432.7550063
灯是 红灯
小车等红灯中 1617530433.7559776
灯是 红灯
灯是 红灯
灯是 绿灯
小车可以走了 1617530435.7581854
"""