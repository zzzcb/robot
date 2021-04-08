import requests
import gevent
from gevent import monkey
monkey.patch_all()

def download_img():
    #requests.get() #如果遇到IO就会切换
    pass 

if __name__ == "__main__":

    img_url1 = "http://img.mp.itc.cn/upload/20170716/8e1b835f198242caa85034f6391bc27f.jpg"
    img_url2 = "http://img.mp.sohu.com/upload/20170529/d988a3d940ce40fa98ebb7fd9d822fe2.png"
    img_url3 = "http://image.uczzd.cn/11867042470350090334.gif?id=0&from=export"
    # 开启协程 调用下载方法
    gevent.joinall([
        gevent.spawn(download_img, img_url1, "1.gif"),
        gevent.spawn(download_img, img_url2, "2.gif"),
        gevent.spawn(download_img, img_url3, "3.gif")
    ]) 