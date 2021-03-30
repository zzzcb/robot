import socket,time

fd_ser = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # 端口会 动态分配

# 每隔1s 向局域网中的 发送广播 
while True:
    fd_ser.sendto(b"hello world",("192.168.2.255",3333)) # 向192.168.2.xxx 下的设备 的 3333 发送 广播 
    time.sleep(1)

fd_ser.close()



