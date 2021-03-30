import sys  
import os 
import time  

os.chdir(os.path.dirname(sys.argv[0])) # 切换到当前目录 
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # 设置环境变量，隐藏刚开始的提示信息 

import random  
import pygame  
from pygame import locals
from src.HeroPlane import HeroPlane
from src.EnemyPlane import EnemyPlane


def main():
    pygame.init()
    bgSurface = pygame.image.load("img/img_bg_level_1.jpg") 

    windowSurface = pygame.display.set_mode((bgSurface.get_width(),bgSurface.get_height()))
    windowSurface.blit(bgSurface,[0,0])

    pygame.display.set_caption("飞机大战")
    iconSurface = pygame.image.load("img/app.ico")
    pygame.display.set_icon(iconSurface)

    windowW = windowSurface.get_width()
    windowH = windowSurface.get_height()   
    heroPlane = HeroPlane("img/hero2.png",windowW,windowH)

    enemys = [] # 敌机 列表  最多 5 个敌机  
    bloods = 3 # 血量为 3  

    gameOverTextSurface = pygame.font.Font("font/happy.ttf",80).render("Game Over",True,[255,255,255])#抗锯齿,白色

    # 渲染循环 
    while True:            
        windowSurface.blit(bgSurface,[0,0]) # 防止重影 

        # 事件处理 
        for evt in pygame.event.get():
            if evt.type == locals.QUIT: 
                pygame.quit()
                sys.exit(0)
            
            if heroPlane.isGameOver():
                continue

            if evt.type == locals.KEYDOWN:
                if evt.key == locals.K_j: # 发射子弹 
                    heroPlane.shoot()

            statusList = pygame.key.get_pressed() # 所有按键 的status 
            if 1 in statusList: # 有按键 按下 
                if statusList[locals.K_w]: # W 键 按下 
                    heroPlane.move_up(5)
                elif statusList[locals.K_s]: # S 键 按下 
                    heroPlane.move_down(5)
                elif statusList[locals.K_a]: # A 键 按下 
                    heroPlane.move_left(5)
                elif statusList[locals.K_d]: # D 键 按下 
                    heroPlane.move_right(5)

        # 渲染我方战机  
        windowSurface.blit(heroPlane.heroSurface,heroPlane.heroInitPos)

        enemyRemoves = []
        bulletRemoves = []

        # 如果敌机不够，添加 
        while len(enemys) < 5: # 要加满 到5个飞机 
            enemy = EnemyPlane(f"img/img-plane_{random.randint(1,7)}.png",windowW,windowH)
            enemys.append(enemy)
        # 渲染敌机  
        for enemy in enemys: 
            windowSurface.blit(enemy.enemyPlaneSurface,enemy.enemyInitPos)
        # 渲染 hero的子弹  
        for bullet in heroPlane.bullets:
            windowSurface.blit(bullet.bulletSurface,bullet.bulletInitPos)

        if heroPlane.isGameOver():
            textPos =[(windowW - gameOverTextSurface.get_width())/2,(windowH - gameOverTextSurface.get_height())/2]
            windowSurface.blit(gameOverTextSurface,textPos)

            time.sleep(0.01)
            pygame.display.flip()
            continue

        # 循环查看 敌机是否 被子弹干死 或 碰地  或 碰到我方飞机 
        for idx,enemy in enumerate(enemys):
            # 敌机 向下走 0.2  
            enemy.move_down(1)
            if enemy.enemyInitPos[1] > windowH - enemy.h:
                # 敌机 碰地了 
                heroPlane.loss_blood(1) # 掉血 1 
                enemyRemoves.append(idx)

            flag,bulletAttackIdx = enemy.isAttacked(heroPlane.bullets) # 返回值:flag 是否击中,bulletAttackIdx是，击中敌机的子弹索引 
            if flag:
                enemyRemoves.append(idx)
                bulletRemoves.append(bulletAttackIdx)
            
            # enemTopCenterPos
            etcp = [enemy.enemyInitPos[0]+enemy.w/2,enemy.enemyInitPos[1] + enemy.h]
            if heroPlane.isTouched(etcp):
                heroPlane.loss_blood(1)
                enemyRemoves.append(idx)


        # 循环查看 子弹是否越界  
        for idx,bullet in enumerate(heroPlane.bullets):
            # 子弹  每次渲染 移动 2
            bullet.attack(2)

            # 记录 越界的子弹 的idx 
            if bullet.bulletInitPos[1] < 0:
                bulletRemoves.append(idx)

        # 删除 被击中的敌机  
        #for idx in enemyRemoves: # 这样会有bug,例如enemyRemoves 是[1,4]， enemys 先pop(1),然后如果再pop(4) 就不行了
        #    enemys.pop(idx)
        enemyRemoves.sort(reverse=True) # enemyRemoves 从大到小排序,先pop(4) 后pop(1)
        for idx in enemyRemoves: 
            enemys.pop(idx)

        # 删除 越界的子弹 和 击中敌机 的子弹 
        bulletRemoves = list(set(bulletRemoves)) # 可能 一个子弹 杀死两个敌机 ，需要去重 ,删除子弹一次就够了 
        bulletRemoves.sort(reverse=True)  # 同上 
        for idx in bulletRemoves:
            heroPlane.bullets.pop(idx) 

        #if len(enemys)<5:  # 测试代码 
        #    print(enemyRemoves,bulletRemoves)

        # 降低fps 
        time.sleep(0.01)

        # 刷新 display 
        pygame.display.flip()





if __name__ == "__main__":
    main()