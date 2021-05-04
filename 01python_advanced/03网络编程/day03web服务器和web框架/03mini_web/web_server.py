import socket 
import os,sys 
from dynamic import web_frame

class WebServer:
    def __init__(self):
        self.__fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    # 构建HTTP数据
    def __formatHttp(self):
        response_line =self.response_line.encode()

        response_body  = self.response_body

        response_header = f"Content-Length:{len(response_body)}\r\n"
        for kv in self.response_header:
            response_header += f"{kv[0]}:{kv[1]}\r\n"
        response_header = response_header.encode()
        response_blank = self.response_blank.encode()

        return response_line + response_header + response_blank + response_body

    def __getReqPath(self,recv_d):
        # 得到请求行  
        idx = recv_d.find("\r\n")
        requestLine = recv_d[:idx]
        return requestLine.split(" ")[1]

    # 解析 HTTP数据 
    def __parseHttp(self,recv_d):
        path = self.__getReqPath(recv_d)
        return path
    
    def __handleRequest(self,fd_conn):
        recv_d = fd_conn.recv(1024).decode() 

        path = self.__parseHttp(recv_d)

        # 动态资源 到 web_frame中去
        if path.endswith(".pyp"):
            env = {}
            env["path"] = path 
            self.response_body = web_frame.application(env,self.start_response)# env:dict 
        # 静态资源
        else: 

            try:
                with open(f"static{path}","rb") as f:
                    self.response_body = f.read() 

                if path.endswith(".jpeg"):
                    self.start_response("200 OK",[("Content-type","image/jpeg")])
                if path.endswith(".ico"):
                    self.start_response("200 OK",[("Content-type","image/ico")])
            except:
                self.start_response("404 Not Found",[("Content-type","text/html;charset=utf8;")])
                self.response_body = f"您请求的静态资源{path} Not Found".encode()

        fd_conn.send(self.__formatHttp())
    
    def start_response(self,status,response_header):# status:str,response_header:[(),()]
        self.response_line = f"HTTP/1.1 {status}\r\n"
        self.response_header = response_header
        self.response_blank = "\r\n"

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