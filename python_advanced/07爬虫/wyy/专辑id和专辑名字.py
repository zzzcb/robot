import requests,re,json
# 网易云音乐 

pattern = re.compile(r'<meta property="og:music:album:song" content="title=(.*?);.*?id=(.*?)"/>',re.DOTALL)
d = []
with open("songs.html","r",encoding="utf8") as f: 
    res = pattern.findall(f.read())
    print(res)
    #for singer_id,singer_name in res:
    #    d.append((singer_id,singer_name))

#with open("album_id_name.json","w",encoding="utf8") as f:
#    json.dump(d,f,ensure_ascii=False)


