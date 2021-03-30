import socket,time

fd_ser = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # 端口会 动态分配
#fd_ser.setsockopt() # 设置 允许全局广播 
fd_ser.setsockopt(socket.SOL_SOCKET,socket.SO_BROADCAST,True) # 第一个参数是范围，第二个是key,第三个是val


# 每隔1s 向广域网中的 发送广播  # 但是一般点电脑可以发全局广播，不能收。windows 可以发也可以收(没节操).linux 默认不收全局广播
while True:
    fd_ser.sendto(b"hello world",("255.255.255.255",3333)) # 向xxx.xxx.xxx.xxx 下的设备 的 3333 发送 广播 
    time.sleep(1)    

fd_ser.close()



