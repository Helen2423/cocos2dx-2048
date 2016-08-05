//
//  GameScene.h
//  2048
//
//  Created by CTC on 15/7/16.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "GameDefine.h"
#include "MovedTiled.h"

USING_NS_CC;

class Game : public Layer
{
private:
    // 作为全局变量
    LayerColor *mapColor;
    // 是否开始触摸
    bool m_startMove;
    // 触摸开始的点
    int m_x,m_y;
    E_MOVE_DIR m_dir;
    // 4*4的数组 判断是否有值
    int m_iMap[GAME_ROWS][GAME_COLS];
    // 保存所有块
    Vector<MovedTiled *> m_allTiled;
    // 分数
    int m_iScore;
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    // 移动所有块
    void moveAllTiled(E_MOVE_DIR dir);
    // 产生新块
    void newMovedTiled();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

public:
    static Scene *createScene();
    CREATE_FUNC(Game);
    virtual bool init();
};


#endif /* GameScene_h */
