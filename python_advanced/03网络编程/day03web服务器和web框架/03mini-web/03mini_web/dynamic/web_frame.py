import os ,sys 
os.chdir(os.path.dirname(sys.argv[0]))

def index():
    with open("templates/index.html","rb") as f:
        return f.read()

def center():
    with open("templates/center.html","rb") as f:
        return f.read()

# 传出line,header,都是string，传出的body 是bytes
def application(env,start_response):
    path = env["path"].replace(".pyp",".html")
    if path == "/index.html":
        start_response("200 OK",[("Content-Type","text/html;charset=utf-8"),])
        return index()
    elif path == "/center.html":
        start_response("200 OK",[("Content-Type","text/html;charset=utf-8"),])
        return center()
    else:
        start_response("404 Not Found",[("Content-Type","text/html;charset=utf-8"),])
        return f"您请求的动态资源{path} Not Found".encode()

