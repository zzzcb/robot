import multiprocessing 
import os,sys

def copy_work(file_name, source_dir, dest_dir):
    source_path = os.path.join(source_dir,file_name)
    dest_path = os.path.join(dest_dir,file_name)
    print(source_path,dest_path)

    print(source_path, "----->", dest_path)
    # 打开源文件、创建目标文件
    with open(source_path,"rb") as source_file:
        with open(dest_path,"wb") as dest_file:
            while True:
                # 循环读取数据
                file_data = source_file.read(1024)
                if file_data:
                    # 循环写入到目标文件
                    dest_file.write(file_data)
                else:
                    break
if __name__ == "__main__":
    os.chdir(os.path.dirname(sys.argv[0]))
    source_dir = "d:/music/"
    dest_dir = "d:/music_bak/"
    file_lists = os.listdir(source_dir)
    pool = multiprocessing.Pool(3)
    for filename in file_lists:
        pool.apply_async(copy_work,(filename,source_dir,dest_dir,)) # no block

    pool.close() # no new task
    pool.join()
    print("执行完毕")
