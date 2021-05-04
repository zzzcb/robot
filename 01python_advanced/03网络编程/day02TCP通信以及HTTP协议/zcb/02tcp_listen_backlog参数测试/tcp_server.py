import socket  
import time 


fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM) 

fd_ser.bind(("",8080))
fd_ser.listen(2) 
time.sleep(20) # 先不 accept，20s后再 accept 

while True:
    fd_conn,conn_cli_addr = fd_ser.accept()
    recv_d = fd_conn.recv(1024)
    print(f"[from {conn_cli_addr[0]}:{conn_cli_addr[1]}]: {recv_d.decode()}")

    fd_conn.close()

fd_ser.close()
