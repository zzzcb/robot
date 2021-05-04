# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter


class Test01Pipeline:
    def open_spider(self,spider):
        #print("开始了")
        # 打开数据库 
        self.cnt = 0

    def process_item(self, item, spider):
        print("================>",item)
        # 存入数据库 ，可以使用SQLalchemy 等orm 
        self.cnt += 1
        return item

    def close_spider(self,spider):
        #print("结束了")
        # 关闭数据库 
        print(f"===================================\n最终爬取了{self.cnt} 条数据\n================================\n")



