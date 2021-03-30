"""
一个文件下载器的客户端，将服务器的指定文件下载到桌面
./1.txt -> C:/Users/Poplar/Desktop/1.txt

1. 导入依赖
2. 创建TCP socket
3. 连接TCP服务器
4. 接收用户输入的文件名
5. 将文件名发送给服务器
6. 在本地创建同名的文件，等待接收文件数据
7. 循环接收并写入文件数据
8. 关闭TCP socket
"""

# 1. 导入依赖
from socket import *

# 2. 创建TCP socket
tcp_socket = socket(AF_INET, SOCK_STREAM)

# 3. 连接TCP服务器
tcp_socket.connect(("127.0.0.1", 8080))

# 4. 接收用户输入的文件名
filename = input("请输入要下载的文件名:\n")

# 5. 将文件名发送给服务器
tcp_socket.send(filename.encode())

# 6. 在本地创建同名的文件，等待接收文件数据
filepath = "d:/" + filename
with open(filepath, "wb") as f:
    while True:
        # 7. 循环接收并写入文件数据
        recv_data = tcp_socket.recv(4096)
        if recv_data:
            f.write(recv_data)
        else:
            print("文件写入完毕:", filepath)
            break

# 8. 关闭TCP socket
tcp_socket.close()