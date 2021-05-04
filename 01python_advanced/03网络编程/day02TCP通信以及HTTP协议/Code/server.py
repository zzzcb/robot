"""
文件下载器的服务端，接收客户端的文件名，把文件以流的形式返回给客户端

1. 导入依赖
2. 创建TCP socket
3. 绑定IP和端口号
4. 开启监听，变为被动模式
5. 等待客户端接入
6. 接收客户端传来的文件名
7. 打开文件
8. 循环读取文件内容，发送给客户端，最后关闭文件
9. 关闭客户端
10.关闭服务器

"""
# 1. 导入依赖
from socket import *

# 2. 创建TCP socket
tcp_server_socket = socket(AF_INET, SOCK_STREAM)

# 当前socket对象关闭时，立即释放端口。
# .setsockopt(那个级别的套接字,属性名,属性值 )
# socket.SOL_SOCKET  当前套接字
# socket.SO_REUSEADD 设置地址重用  True 可以重用  False 不能重用
tcp_server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, True)

# 3. 绑定IP和端口号
tcp_server_socket.bind(("", 8080))

# 4. 开启监听，变为被动模式
tcp_server_socket.listen(128)

print("服务器已开启，等待客户端接入")
while True:
    # 5. 等待客户端接入
    tcp_client_socket, ip_port = tcp_server_socket.accept()
    print("有新的客户端接入：", ip_port)

    # 6. 接收客户端传来的文件名
    bytes_data = tcp_client_socket.recv(1024)
    filename = bytes_data.decode()
    print(filename)

    # 7. 打开文件
    try:
        with open(filename, "rb") as f:
            while True:
                # 8. 循环读取文件内容，
                data = f.read(4096)
                if data:
                    # 发送给客户端，最后关闭文件
                    tcp_client_socket.send(data)
                else:
                    break
    except:
        print("文件不存在或打开失败: ", filename)
    else:
        print("文件已读取发送完毕！", filename)

    # 9. 关闭客户端
    tcp_client_socket.close()

# 10.关闭服务器
tcp_server_socket.close()