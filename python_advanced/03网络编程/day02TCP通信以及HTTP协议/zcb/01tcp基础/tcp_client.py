import socket


fd_cli = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
fd_cli.connect(("127.0.0.1",8080))


fd_cli.send(input("to sever>>>").encode())

fd_cli.close()
