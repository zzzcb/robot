from .BasePage import BasePage
from locals import (Color,WINDOW_W,WINDOW_H)

class GameOverPage(BasePage):

    def __init__(self,window):
        # 加载 "Game Over" 文字  
        super().__init__(window)
        self.gOTextSurface =  self.bigFont.render("Game Over",True,Color.WHITE)
        self.gOTextPos = [(WINDOW_W-self.gOTextSurface.get_width())/2,(WINDOW_H-self.gOTextSurface.get_height())/2]

        self.tipTextSurface = self.smallFont.render("Press a key to play",True,Color.RED)
        self.tipTextPos = [WINDOW_W - self.tipTextSurface.get_width() - 50,WINDOW_H - self.tipTextSurface.get_height() - 50]


    def display(self):
        self.window.blit(self.gOTextSurface,self.gOTextPos)
        self.window.blit(self.tipTextSurface,self.tipTextPos)

    def keyDown(self,key):
        pass 
