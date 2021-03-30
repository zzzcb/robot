import socket  


fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM) 

fd_ser.bind(("",8080))
fd_ser.listen() #规定了内核应该为相应的套接字排队的最大连接个数,linux 上该参数无效默认最大！ 


fd_conn,conn_cli_addr = fd_ser.accept()
recv_d = fd_conn.recv(1024)
print(f"[from {conn_cli_addr[0]}:{conn_cli_addr[1]}]: {recv_d.decode()}")

fd_conn.close()
fd_ser.close()
