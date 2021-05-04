"""
所有界面的父类 
"""
from locals import PageType
import pygame 
import abc  

class BasePage(metaclass=abc.ABCMeta):
    # 当前界面类型 
    pageType =  PageType.SPLASH
    
    def __init__(self,window):
        self.window = window 
        # 大字体  
        self.bigFont = pygame.font.Font("resources/ARBERKLEY.ttf",100)
        # 小字体 
        self.smallFont = pygame.font.Font("resources/ARBERKLEY.ttf",20)

    @abc.abstractmethod
    def display(self):
        pass 


    @abc.abstractmethod
    def keyDown(self,key):
        pass 


























