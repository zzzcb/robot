import socket  

fd_cli = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
fd_cli.connect(("www.baidu.com",80))


request_line = "GET / HTTP/1.1\r\n"
request_header = "Host:www.baidu.com\r\n"
request_blank = "\r\n"
request_body =  "\r\n"  #b"" or ""
request_data = request_line + request_header + request_blank + request_body
fd_cli.send(request_data.encode())

# 接收响应内容 并解析内容 
response = b""
while True:
    ret = fd_cli.recv(1024)
    if ret:
        response += ret 
    else:
        break

idx = response.find(b"\r\n\r\n")
with open("response.html","wb") as f:
    f.write(response[idx+4:])

fd_cli.close()