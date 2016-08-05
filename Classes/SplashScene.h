//
//  SplashScene.h
//  2048
//
//  Created by CTC on 15/7/16.
//
//

#ifndef SplashScene_h
#define SplashScene_h
#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class Splash : Layer
{
public:
    static Scene *createScene();
    CREATE_FUNC(Splash);
    virtual bool init();
    // 实现3秒自动调整到游戏画面
    void jumpToGame(float t);
};

#endif /* SplashScene_h */
