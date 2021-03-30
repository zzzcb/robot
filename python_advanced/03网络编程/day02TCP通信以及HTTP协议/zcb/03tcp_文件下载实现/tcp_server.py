import socket  
import os ,sys 
cur_fname = os.path.abspath(sys.argv[0])
os.chdir(os.path.dirname(cur_fname)) 

basedir = input("请输入服务器端供下载的目录>>>")

from utils.utils import Tree
def get_server_dir_info():
    tree = Tree()
    tree.walk(basedir)
    return tree.retString

fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
fd_ser.bind(("",8080))
fd_ser.listen()
while True:
    fd_conn,conn_cli_addr = fd_ser.accept()
    fd_conn.send(get_server_dir_info().encode())
    filename = os.path.join(basedir,fd_conn.recv(1024).decode())
    #print(f"ip,port[{conn_cli_addr[0]},{conn_cli_addr[1]}] want to download {filename} file.")
    if os.path.exists(filename):
        with open(filename,"rb") as f:
            while True:
                d = f.read(1024)
                if d: 
                    fd_conn.send(d)
                else: #读完了
                    break
    else:
        fd_conn.send(b"-1") # 不存在 该文件

    fd_conn.close()
    
fd_ser.close()