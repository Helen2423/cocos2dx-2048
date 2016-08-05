//
//  GameDefine.h
//  2048
//
//  Created by CTC on 15/7/16.
//
//

#ifndef GameDefine_h
#define GameDefine_h

//此头文件用来定义大小 以适应不同的屏幕
//屏幕的大小
#define GAME_SCREEN_WIDTH 640
#define GAME_SCREEN_HEIGHT 1136
//网格的大小
#define GAME_TILED_WIDTH 130
//网格间距离
#define GAME_TILED_BOARD_WIDTH 5
//游戏4行4列 如果想建更多格子可以方便修改
#define GAME_ROWS 4
#define GAME_COLS 4
enum E_MOVE_DIR {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


#endif /* GameDefine_h */
