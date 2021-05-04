import os ,sys 
os.chdir(os.path.dirname(sys.argv[0]))

# 传出line,header,都是string，传出的body 是bytes
def application(env,start_response):
    path = env["path"]
    if path == "/favicon.ico":
        with open("favicon.ico","rb") as f:
            response_body = f.read()
        start_response("200 OK",[("Content-Type","image/x-icon"),])
        return response_body
    else:
        response_body = f"这次请求的路径是:{path}".encode()
        start_response("200 OK",[("Content-Type", "text/html; charset=utf-8"),])
        return response_body



