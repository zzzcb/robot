"""
敌方飞机 
"""
import pygame  
import random  

class EnemyPlane:
    def __init__(self,imgPath,windowW,windowH):
        self.enemyPlaneSurface = pygame.image.load(imgPath)
        self.w = self.enemyPlaneSurface.get_width()
        self.h = self.enemyPlaneSurface.get_height()

        posRange = [0,int(windowW - self.w),0,int(1/3*windowH - self.h)] # 随机位置的范围 
        self.enemyInitPos = [random.randint(posRange[0],posRange[1]),random.randint(posRange[2],posRange[3])]  # 随机生成一个位置  注：randint 【a，b】 


    def _isInRect(self,pos): 
        """
        pos:[a,b] 是否在 self.enemyInitPos self.w self.h 里面  
        """
        posX = self.enemyInitPos[0]
        posY = self.enemyInitPos[1]
        if pos[0] < posX or pos[1] <posY or pos[0] > posX + self.w or pos[1] > posY + self.h:  
            # pos 点 不在范围内   
            return False
        else:
            return True

    def isAttacked(self,allBullets):
        """
        allBullets 是所有的子弹: hero.bullets 
        """
        # 简便一些  bullet的topCenter 进入敌机rect 就算击中  
        for idx,bullet in enumerate(allBullets):
            topCenterPos = [bullet.bulletInitPos[0]+bullet.w/2,bullet.bulletInitPos[1]]
            if self._isInRect(topCenterPos): #碰撞了 
                return (True,idx)
        
        return (False,-1)  # 没有碰撞 

    def move_down(self,distance): # 敌机 向下走  
        self.enemyInitPos[1] = self.enemyInitPos[1] + distance

