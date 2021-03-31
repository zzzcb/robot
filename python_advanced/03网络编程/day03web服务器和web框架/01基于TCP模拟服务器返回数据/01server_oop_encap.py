import socket 
import os,sys 

class WebServer:
    def __init__(self):
        self.__fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    def __formatDataToCli(self,path):
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

    def __getReqPath(self,recv_d):
        # 得到请求行  
        idx = recv_d.find("\r\n")
        requestLine = recv_d[:idx]
        return requestLine.split(" ")[1]

    def __handleRequest(self,fd_conn):
        recv_d = fd_conn.recv(1024).decode() 
        path = self.__getReqPath(recv_d)
        fd_conn.send(self.__formatDataToCli(path))

    def run(self,ip="",port=80):
        self.__fd_ser.bind((ip,port))
        self.__fd_ser.listen()
        while True:
            fd_conn,cli_addr = self.__fd_ser.accept()
            self.__handleRequest(fd_conn)
            fd_conn.close()

        self.__fd_ser.close()


if __name__ =="__main__":
    os.chdir(os.path.dirname(sys.argv[0]))
    server = WebServer()
    #server.run("127.0.0.1",8080)
    server.run() 