from enum import Enum

# 窗口的 w ,h 
WINDOW_W = 600 
WINDOW_H = 480  

# 网格数量  
HGRIDCOUNT = 30
VGRIDCOUNT = 24 

# 每个网格的大小 
CELLSIZE = 20

# 方向 
class Direction(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3

# 页面类型 
class PageType(Enum):
    SPLASH = 0 # 初始界面
    GAME = 1 # 游戏界面 
    GAMEOVER = 2  # 游戏结束界面  

# 常用颜色 
class Color:
    WHITE = (255, 255, 255)
    BLACK = ( 0, 0, 0)
    RED = (255, 0, 0)
    GREEN = ( 0, 255, 0)
    DARKGREEN = ( 0, 155, 0)
    DARKGRAY = ( 40, 40, 40)
    BGCOLOR = BLACK

