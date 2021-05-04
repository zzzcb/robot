"""
子弹
"""
import pygame 
import time 

class Bullet:
    def __init__(self,imgPath,heroTopCenterPos):
        """
        imgPath:str 
        heroTopCenterPos:[a,b]
        """
        self.bulletSurface = pygame.image.load(imgPath)  
        self.w = self.bulletSurface.get_width()
        self.h = self.bulletSurface.get_height()

        self.bulletInitPos = [heroTopCenterPos[0] - self.w/2, heroTopCenterPos[1] - self.h]
    

    def attack(self,distance):
        self.bulletInitPos[1] = self.bulletInitPos[1] - distance








