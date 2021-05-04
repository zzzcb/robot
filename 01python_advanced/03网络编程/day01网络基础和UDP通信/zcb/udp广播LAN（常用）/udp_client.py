import socket 
import time 
fd_cli = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

fd_cli.bind(("",3333)) # 本机任意网卡都可以

while True:
    recv_d,server_addr = fd_cli.recvfrom(1024)
    cur_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    print(f"[{cur_time}] [from broadcast,ip is{server_addr[0]},port is {server_addr[1]}]:{recv_d.decode()}")

fd_cli.close()

