import socket 

fd_ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
fd_ser.bind(("",80))
fd_ser.listen()

def formatDataToCli():
    response_line = "HTTP/1.1 200 OK\r\n"
    response_blank = "\r\n"
    response_body = """<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hello World</title>
</head>
<body>
    <h1>Hello World</h1>
</body>
</html>"""
    response_header = f"Content-Type: text/html; charset=utf-8\r\nContent-Length:{len(response_body)}\r\n"

    retStr = response_line + response_header + response_blank+response_body
    return retStr.encode()


def handleRequest(fd_conn):
    recv_d = fd_conn.recv(1024).decode()
    print(f"[from client]:\n{recv_d}")
    fd_conn.send(formatDataToCli())

while True:
    fd_conn,cli_addr = fd_ser.accept()
    handleRequest(fd_conn)
    fd_conn.close()


fd_ser.close()







