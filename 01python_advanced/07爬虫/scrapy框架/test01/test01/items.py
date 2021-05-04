# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


# 明确目标 
class MovieItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()

    # 电影的名字
    film_name = scrapy.Field()
    # 电影的海报链接
    film_poster = scrapy.Field()



    





