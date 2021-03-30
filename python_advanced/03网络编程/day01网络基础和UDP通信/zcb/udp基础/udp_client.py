import socket 
fd_cli = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)


while True:
    to_ser_content = input("[to ser]:>>>").encode()
    fd_cli.sendto(to_ser_content,("127.0.0.1",8080))
    recv_d,server_addr = fd_cli.recvfrom(1024)
    print(f"[from server]:{recv_d.decode()}")

fd_cli.close()

