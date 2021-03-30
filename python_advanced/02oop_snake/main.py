import sys  
import os  
os.chdir(os.path.dirname(sys.argv[0]))
os.environ["PYGAME_HIDE_SUPPORT_PROMPT"] = '1'

import pygame 
from pygame import locals as pg_locals
from pages import (SplashPage,GamePage,GameOverPage)
from locals import (WINDOW_W,WINDOW_H,PageType)

def main():
    pygame.init()
    windowSurface = pygame.display.set_mode([WINDOW_W,WINDOW_H])
    pygame.display.set_caption("贪吃蛇")

    clock = pygame.time.Clock()

    # 初始界面 
    page = SplashPage(windowSurface)
    initPageType = PageType.SPLASH 

    # 主循环  
    while True:
        # 页面处理
        if initPageType == PageType.SPLASH  and not isinstance(page,SplashPage):
            page = SplashPage(windowSurface)
        elif initPageType == PageType.GAME and not isinstance(page,GamePage):
            page = GamePage(windowSurface)
        elif initPageType == PageType.GAMEOVER and not isinstance(page,GameOverPage):
            page = GameOverPage(windowSurface)


        # 事件处理  
        if pygame.event.get(pg_locals.QUIT):
            pygame.quit()
            sys.exit(0)

        keyDownEvtList = pygame.event.get(pg_locals.KEYDOWN)
        if keyDownEvtList:
            page.keyDown(keyDownEvtList[0].key)
            if not isinstance(page,GamePage):
                initPageType = PageType.GAME
            
        # 展示界面 
        page.display()

        if isinstance(page,GamePage) and page.isGameOver():  
            initPageType = PageType.GAMEOVER

        # 刷新 
        pygame.display.flip()

        # 帧率 
        clock.tick(4)  #4 fps 


if __name__ == "__main__":
    main()









