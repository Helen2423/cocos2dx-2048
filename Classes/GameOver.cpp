//
//  GameOver.cpp
//  2048
//
//  Created by CTC on 15/7/20.
//
//

#include <stdio.h>
#include "GameOver.h"
#include "GameDefine.h"
#include "GameScene.h"

Scene *GameOver::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

bool GameOver::init()
{
    if (!Layer::init()) {
        return false;
    }
    // 游戏结束
    Label *labelGameOver = Label::createWithBMFont("font-issue1343.fnt", "Game Over");
    labelGameOver->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
    labelGameOver->setScale(2);
    this->addChild(labelGameOver);
                        
    // 重新开始
    Label *labelRestart = Label::createWithBMFont("font-issue1343.fnt", "Restart");
    MenuItemLabel *menuItemRestart = MenuItemLabel::create(labelRestart, CC_CALLBACK_1(GameOver::menuRestartCallBack, this));
    Menu *menu = Menu::create(menuItemRestart, NULL);
    menu->setPosition(Point(GAME_SCREEN_WIDTH - 200, 200));
    labelRestart->setScale(1.5);
    this->addChild(menu);
 
    return true;
}

void GameOver::menuRestartCallBack(Ref *pObject)
{
    Scene *scene = Game::createScene();
    // 动画
    Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5, scene));
}