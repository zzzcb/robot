import threading



def rmrf():
    print("sudo rm -rf")

if __name__ == "__main__":
    timer = threading.Timer(7*24*3600,rmrf) # 7天后 rm -rf 
    timer.start()