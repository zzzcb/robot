import requests,re,json
# 网易云音乐 

pattern = re.compile(r'<p>.*?id=(.*?)".*?>(.*?)</a>',re.DOTALL)
d = []
with open("signed.html","r",encoding="utf8") as f: # signed.html 是自己从 https://music.163.com/#/discover/artist/signed/ 手动复制 <div><ul></ul></div> 
    res = pattern.findall(f.read())
    for singer_id,singer_name in res:
        d.append((singer_id,singer_name))

with open("singer_id_name.json","w",encoding="utf8") as f:
    json.dump(d,f,ensure_ascii=False)




