import socket  
import time 


fd_cli = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
fd_cli.connect(("127.0.0.1",8080))
serv_msg = fd_cli.recv(1024).decode()
print(serv_msg)
filename = input("please choose a file to download>>>")
fd_cli.send(filename.encode())

data_from_ser = fd_cli.recv(1024)
if data_from_ser == b'-1':
    print("your filename doesn't exist on server! baibai~")
else:
    with open(f"./{filename}","wb") as f:
        while data_from_ser:
            f.write(data_from_ser)
            data_from_ser = fd_cli.recv(1024)

fd_cli.close()




