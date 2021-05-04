import socket 
import os,sys 
os.chdir(os.path.dirname(sys.argv[0]))

fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
fd_ser.bind(("",80))
fd_ser.listen()

def formatDataToCli(path):
    response_line = "HTTP/1.1 200 OK\r\n".encode()
    response_blank = "\r\n".encode()
    if path == "/favicon.ico":
        with open("favicon.ico","rb") as f:
            response_body = f.read()
            response_header = f"Content-Type: image/x-icon\r\nContent-Length:{len(response_body)}\r\n".encode()
    else:
        response_body = f"这次请求的路径是:{path}\r\n".encode()
        response_header = f"Content-Type: text/html; charset=utf-8\r\nContent-Length:{len(response_body)}\r\n".encode()

    retStr = response_line + response_header + response_blank+response_body
    return retStr


def getReqPath(recv_d):
    # 得到请求行  
    idx = recv_d.find("\r\n")
    requestLine = recv_d[:idx]
    return requestLine.split(" ")[1]


def handleRequest(fd_conn):
    recv_d = fd_conn.recv(1024).decode()
    path = getReqPath(recv_d)
    fd_conn.send(formatDataToCli(path))

while True:
    fd_conn,cli_addr = fd_ser.accept()
    handleRequest(fd_conn)
    fd_conn.close()


fd_ser.close()







