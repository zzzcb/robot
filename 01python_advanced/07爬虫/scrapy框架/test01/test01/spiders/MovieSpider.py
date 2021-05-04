import scrapy


class MoviespiderSpider(scrapy.Spider):
    name = 'MovieSpider'
    allowed_domains = ['ygdy8.net']
    start_urls = ['https://www.ygdy8.net/html/gndy/dyzz/list_23_1.html']

    def parse(self, response): # 这个response是解析 start url 得到的!
        ret = response.css(".ulink::attr('href')").extract()  #css选择器去寻找 |  a标签 -> ::attr('href') ::text
        #print("=================start==================")
        for new_url in ret:
            full_url = "https://www.ygdy8.net/"+new_url
            yield scrapy.Request(full_url,callback=self.parse_item) # callback 请求回来后，如何处理 
            # yield 返回给 调度器中 

        #print("=================end====================")

        # start 页面爬取完毕，下面爬取其他页面` 
        for page in range(2,11):
            url = f'https://www.ygdy8.net/html/gndy/dyzz/list_23_{page}.html'
            #print("==============zcb===================",url)
            yield scrapy.Request(url,callback=self.parse)



    def parse_item(self,response): # callback 函数 
        # 获取名字  
        film_name = response.css("#Zoom").re(r'◎译　　名(.*?)<br>')
        film_name = film_name[0] if film_name else None

        film_poster = response.css("#Zoom").re(r'<img.*?src="(.*?)"')
        film_poster = film_poster[0] if film_poster else None

        from test01.items import MovieItem
        item = MovieItem()
        item['film_name'] = film_name
        item['film_poster'] = film_poster

        yield item  # yield 返回给 管道中 






