import requests,json,re

album_pattern = re.compile(r'<div class="u-cover.*?title="(.*?)".*?<a href="/album\?id=(.*?)"',re.DOTALL)
song_pattern = re.compile(r'<meta property="og:music:album:song" content="title=(.*?);.*?id=(.*?)"/>',re.DOTALL)
final_data = []
with open("singer_id_name.json","r",encoding="utf8") as f:
    for singer_id,singer_name in json.load(f):
        singer = {"singer_id":singer_id,"singer_name":singer_name,"albums":[]}
        # 所有专辑 url = "/artist/album?id="+singer_id
        url_albums = f"https://music.163.com/artist/album?id={singer_id}&limit=200" # 该 歌手下的所有专辑
        response = requests.get(url_albums)
        if response.status_code == 200:
            for album_name,album_id in album_pattern.findall(response.content.decode()):
                album = {"album_id":album_id,"album_name":album_name,"songs":[]}
                url_songs = f"https://music.163.com/album?id={album_id}" #  该专辑下的所有 歌曲 
                response = requests.get(url_songs)
                if response.status_code == 200:
                    for song_name,song_id in song_pattern.findall(response.content.decode()):
                        album["songs"].append({"song_id":song_id,"song_name":song_name})
                singer["albums"].append(album)
        final_data.append(singer)

with open("final_data.json","w",encoding="utf8") as f:
    json.dump(final_data,f,ensure_ascii=False)
