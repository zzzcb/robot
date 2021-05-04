from .BasePage import BasePage
import pygame  
from pygame import locals as pg_locals
from locals import (Color,WINDOW_W,WINDOW_H,HGRIDCOUNT,VGRIDCOUNT,CELLSIZE,Direction)
import random

class GamePage(BasePage):
    def __init__(self,window):
        super().__init__(window)

        xIdx = random.randint(0+5,HGRIDCOUNT - 1 - 5) # [5,24] 一开始是水平向右 
        y = random.randint(0,VGRIDCOUNT - 1)*CELLSIZE # [0,23]
        self.snakePos = [(xIdx*CELLSIZE,y),((xIdx-1)*CELLSIZE,y),((xIdx-2)*CELLSIZE,y)] #蛇 初始的三个方块  
        self.snakeDirection = Direction.RIGHT # 蛇的 方向,初始为 右

        self.applePos = self.__getApplePos() # 苹果的位置  

        self.score = 0 # 得分 
        self.scorePos = [WINDOW_W - 130 ,20]

    def display(self):
        self.window.fill(Color.BLACK)
        self.drawGrid()
        self.drawSnake()
        self.drawApple()

        self.autoMove()
        self.eatApple() # 每次都检测一下是否 吃苹果
        self.drawScore()

    def autoMove(self):
        # 让蛇 动起来  
        self.lastPos = self.snakePos.pop() # 将最后一个弹出  
        headPos = self.snakePos[0]
        x = headPos[0]
        y = headPos[1]

        direction = self.snakeDirection
        if direction == Direction.UP: # 上 
            self.snakePos.insert(0,(x,y-CELLSIZE))#  并在idx =0 新增一个 
        elif direction == Direction.DOWN: # 下 
            self.snakePos.insert(0,(x,y+CELLSIZE))
        elif direction == Direction.LEFT: # 左 
            self.snakePos.insert(0,(x-CELLSIZE,y))
        elif direction == Direction.RIGHT: # 右 
            self.snakePos.insert(0,(x+CELLSIZE,y))

    def __getApplePos(self):
        xAppleIdx = random.randint(0,HGRIDCOUNT - 1) 
        yAppleIdx = random.randint(0,VGRIDCOUNT - 1)
        return (xAppleIdx*CELLSIZE,yAppleIdx*CELLSIZE)


    
    def drawApple(self):
        # 画苹果           
        pygame.draw.rect(self.window,Color.RED,[self.applePos[0],self.applePos[1],CELLSIZE,CELLSIZE])

        
    def drawSnake(self):
        # 画蛇
        for pos in self.snakePos:
            pygame.draw.rect(self.window,Color.DARKGREEN,[pos[0],pos[1],CELLSIZE,CELLSIZE])
            pygame.draw.rect(self.window,Color.GREEN,[pos[0]+5,pos[1]+5,CELLSIZE-10,CELLSIZE-10])

    def drawGrid(self):
        # 绘制网格  
        for colIdx in range(1,HGRIDCOUNT):
            x = colIdx*CELLSIZE
            pygame.draw.line(self.window,Color.DARKGRAY,[x,0],[x,WINDOW_H])
        
        for rowIdx in range(1,VGRIDCOUNT):
            y = rowIdx*CELLSIZE
            pygame.draw.line(self.window,Color.DARKGRAY,[0,y],[WINDOW_W,y])

    def drawScore(self):
        scoreSurface = self.smallFont.render(f"Score: {self.score}",True,Color.WHITE)
        self.window.blit(scoreSurface,self.scorePos)


    def keyDown(self,key):
        oldDirection = self.snakeDirection
        if key == pg_locals.K_w and oldDirection != Direction.DOWN: # 上   
            self.snakeDirection = Direction.UP
        elif key == pg_locals.K_s and oldDirection != Direction.UP: # 下
            self.snakeDirection = Direction.DOWN
        elif key == pg_locals.K_a and oldDirection != Direction.RIGHT: # 左   
            self.snakeDirection = Direction.LEFT
        elif key == pg_locals.K_d and oldDirection != Direction.LEFT: # 右   
            self.snakeDirection = Direction.RIGHT
    
    def eatApple(self):
        # 是否吃到苹果 
        if self.__isEatApple():
            self.snakePos.append(self.lastPos) # 吃到 食物，再将 autoMove 时pop 出的 方块重新 append 进去  
            self.applePos = self.__getApplePos()
            self.score = self.score + 100

    def __isEatApple(self):
        return self.applePos == self.snakePos[0]

    def __isEatSelf(self):
        # 是否咬到 自己  
        nextPos = self.snakePos[0]
        for pos in self.snakePos[1:]:
            if pos == nextPos:
                return True
        return False

    def isGameOver(self):
        headPos = self.snakePos[0]

        # 碰墙了 
        if headPos[0] < 0 or headPos[1] < 0 or headPos[0] > WINDOW_W - CELLSIZE or headPos[1]> WINDOW_H - CELLSIZE:
            return True

        # 咬到自己了 
        if self.__isEatSelf():
            return True

        return False
