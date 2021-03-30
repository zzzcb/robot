"""
我方飞机
"""
import pygame  
from src.Bullet import Bullet


class HeroPlane:
    def __init__(self,imgPath,windowW,windowH):
        self.heroSurface = pygame.image.load(imgPath)  

        self.w = self.heroSurface.get_width()
        self.h = self.heroSurface.get_height()
        self.windowW = windowW
        self.windowH = windowH

        self.heroInitPos = [(windowW - self.w)/2,windowH - self.h - 50]
        self.bullets = []

        self._blood = 3  # 血量  


    def isTouched(self,enemyTopCenterPos): # 是否被 敌机 碰到,敌机 topCenter 进入 hero rect 就算碰到 
        """
        enemyTopCenterPos:[a,b] 是否在 self.heroInitPos self.w self.h 里面  
        """
        posX = self.heroInitPos[0]
        posY = self.heroInitPos[1]

        etcp = enemyTopCenterPos
        if etcp[0] < posX or etcp[1] <posY or etcp[0] > posX + self.w or etcp[1] > posY + self.h:  
            # pos 点 不在范围内   
            return False
        else:
            return True



    def isGameOver(self):
        if self._blood <= 0:
            return True
        return False
    
    def loss_blood(self,val):
        self._blood = self._blood - val
    
    def shoot(self):
        heroTopCenterPos = [self.heroInitPos[0]+self.w*1/2,self.heroInitPos[1]]
        self.bullets.append(Bullet("img/bullet_8.png",heroTopCenterPos))



    def move_up(self,distance):
        val = self.heroInitPos[1]
        if val >= distance:
            self.heroInitPos[1] = val - distance # up 
        else:
            print("上碰壁")

    def move_down(self,distance):
        val = self.heroInitPos[1]
        if val <= self.windowH -self.h - distance:
            self.heroInitPos[1] = val + distance # down
        else:
            print("下碰壁")

    def move_left(self,distance):
        val = self.heroInitPos[0]
        if val >= distance: # 未碰壁  
            self.heroInitPos[0] = val - distance # left
        else:
            print("左碰壁")

    def move_right(self,distance):            
        val = self.heroInitPos[0]  
        if val <= self.windowW - self.w - distance:
            self.heroInitPos[0] = val + distance # right
        else:
            print("右碰壁")



