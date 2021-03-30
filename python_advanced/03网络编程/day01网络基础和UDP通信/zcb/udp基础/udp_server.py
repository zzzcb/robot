import socket,time

fd_ser = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)#ip4 's udp
fd_ser.bind(("127.0.0.1",8080)) 

while True:
    recv_d,cli_addr = fd_ser.recvfrom(1024)
    print(f"[from cli(port is {cli_addr[1]})]:{recv_d.decode()}")
    to_cli_content = input("[to cli]:>>>").encode()
    fd_ser.sendto(to_cli_content,cli_addr)

fd_ser.close()