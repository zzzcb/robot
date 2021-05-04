import re
import requests 

url = "http://m.youdao.com/translate"

data = {
    "inputtext":"",
    "type":"AUTO",
} 
pattern = re.compile(rb'<ul id="translateResult">.*?<li>(.*?)</li>',re.DOTALL)

while 1:
    inputtext = input("输入要翻译的内容>>>")
    data["inputtext"] = inputtext
    response = requests.post(url,data=data)
    if response.status_code == 200:
        res = pattern.search(response.content)
        if res:
            print(res.group(1).decode())


