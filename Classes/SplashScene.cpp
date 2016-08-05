//
//  SplashScene.cpp
//  2048
//
//  Created by CTC on 15/7/16.
//
//

#include <stdio.h>
#include "SplashScene.h"
#include "GameScene.h"

Scene *Splash::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = Splash::create();
    scene->addChild(layer);
    return scene;
}

bool Splash::init()
{
    if (!Layer::init()) {
        return false;
    }
    //添加背景
    LayerColor *bgColor = LayerColor::create(Color4B(235, 219, 211, 255));
    this->addChild(bgColor);
    //显示游戏名称
    Label *labelGame = Label::createWithBMFont("font-issue1343.fnt", "2048");
    //通过定义的宏来直接调用值的大小
    labelGame->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
    //把字体放大5倍 字体放大会失真
    labelGame->setScale(5);
    this->addChild(labelGame);
    
    //计划任务 3秒后自动跳转到游戏场景 执行一个jumptogame的方法
    this->schedule(schedule_selector(Splash::jumpToGame), 3);
    
    return true;
}

void Splash::jumpToGame(float t)
{
    Scene *scene = Game::createScene();
    Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}