"""
初始界面
"""
from .BasePage import BasePage
from locals import (Color,WINDOW_W,WINDOW_H)

class SplashPage(BasePage):
    def __init__(self,window):
        super().__init__(window)
        # 加载 “Snake” 文本 
        self.snakeTextSurface =  self.bigFont.render("Snake",True,Color.GREEN)
        self.snakeTextPos = [(WINDOW_W -self.snakeTextSurface.get_width())/2,(WINDOW_H -self.snakeTextSurface.get_height())/2]

        # 加载 “Press a key to play”
        self.tipTextSurface = self.smallFont.render("Press a key to play",True,Color.RED)
        self.tipTextPos = [WINDOW_W -self.tipTextSurface.get_width() - 50 ,WINDOW_H -self.tipTextSurface.get_height() - 50]




    def display(self):
        self.window.blit(self.snakeTextSurface,self.snakeTextPos)
        self.window.blit(self.tipTextSurface,self.tipTextPos)

    def keyDown(self,key):
        pass 




        














