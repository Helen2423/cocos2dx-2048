//
//  GameScene.cpp
//  2048
//
//  Created by CTC on 15/7/16.
//
//

#include <stdio.h>
#include "GameScene.h"
#include "GameOver.h"

Scene *Game::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init()
{
    if (!Layer::init()) {
        return false;
    }
    //添加背景
    LayerColor *bgColor = LayerColor::create(Color4B(235, 219, 211, 255));
    this->addChild(bgColor);
    
    // 初始化游戏标题
    Label *labelGame = Label::createWithBMFont("font-issue1343.fnt", "2048");
    labelGame->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - 100));
    labelGame->setScale(2);
    this->addChild(labelGame);
    
    // 初始化游戏网格 LayerColor::create(颜色透明度,宽,高) 灰色
    // 表格 边长＊格数＋间隔＊（格数＋1）
    int tiledmapwidth = GAME_TILED_WIDTH * GAME_ROWS + GAME_TILED_BOARD_WIDTH * (GAME_ROWS + 1);
    int tiledmapheight = GAME_TILED_WIDTH * GAME_COLS + GAME_TILED_BOARD_WIDTH * (GAME_COLS + 1);
    mapColor= LayerColor::create(Color4B(187, 163, 151, 255), tiledmapwidth, tiledmapheight);
    mapColor->setPosition(Point((GAME_SCREEN_WIDTH - tiledmapwidth) / 2, 100));
    this->addChild(mapColor);
    
    // 初始化每个块 4行4列 16个
    for (int row = 0; row < GAME_ROWS; row ++) {
        for (int col = 0; col < GAME_COLS; col++) {
            LayerColor *layerTiled = LayerColor::create(Color4B(251, 227, 206 ,100), GAME_TILED_WIDTH ,GAME_TILED_WIDTH);
            layerTiled->setPosition(Point(GAME_TILED_WIDTH * row + GAME_TILED_BOARD_WIDTH * (row + 1), GAME_TILED_WIDTH * col + GAME_TILED_BOARD_WIDTH * (col + 1)));
            // 小格子加载到mapcolor中
            mapColor->addChild(layerTiled);
        }
    }
    // 初始化网格数组map 4行4列都为0
    for (int i = 0; i < GAME_ROWS; i++) {
        for (int j = 0; j < GAME_COLS; j++) {
            m_iMap[i][j] = 0;
        }
    }
   
    //新建一个块 游戏一开始时出现的数字
    newMovedTiled();
    
    //触摸的处理
    EventListenerTouchOneByOne *event = EventListenerTouchOneByOne::create();
    event->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    event->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    // 被迫弃后的写法_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
    
    // 分数
    m_iScore = 0;
    Label *labelScore = Label::createWithBMFont("font-issue1343.fnt", "Score : 0");
    labelScore->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - 300));
    labelScore->setScale(2);
    this->addChild(labelScore);
    labelScore->setTag(120);

    return true;
}

bool Game::onTouchBegan(Touch *touch, Event *event)
{
    m_x = touch->getLocation().x;
    m_y = touch->getLocation().y;
    m_startMove = true;
    return true;
}

void Game::onTouchMoved(Touch *touch, Event *event)
{
    //鼠标点击坐标(m_x,m_y) 鼠标滑动到的坐标(x,y)
    int x = touch->getLocation().x;
    int y = touch->getLocation().y;
    // 当位移大于10 认为开始移动 ???
    if (m_startMove && (abs(m_x - x) > 10 || abs(m_y - y) > 10)) {
        m_startMove = false;
        //CCLOG("in");
        if (abs(m_x - x) > abs(m_y - y)) {
            if (m_x < x) {
                m_dir = RIGHT;
            }
            else {
                m_dir = LEFT;
            }
        }
        else {
            if (m_y < y) {
                m_dir = UP;
            }
            else {
                m_dir = DOWN;
            }
        }
        moveAllTiled(m_dir);
    }
}

// 移动所有块 消除
void Game::moveAllTiled(E_MOVE_DIR dir)
{
    switch (dir) {
        case UP:
            moveUp();
            break;
        
        case DOWN:
            moveDown();
            break;
        
        case LEFT:
            moveLeft();
            break;
        
        case RIGHT:
            moveRight();
            break;
            
        default:
            break;
    }
    // 播放音乐
    // 分数变化
    Label *labelScore = (Label *)this->getChildByTag(120);
    labelScore->setString(StringUtils::format("Score : %d", m_iScore));
    // 判定输赢
    // 移动过后 产生新块
    newMovedTiled();
    
}

// 产生新块
void Game::newMovedTiled()
{

    // 设置第一个块随机出现位置0-15 其他重新0-14 0-13等等
    // 存储map中空余的空格数
    int freeCount = (GAME_ROWS * GAME_COLS) - (int)m_allTiled.size();
    // 没有空白区域 不用产生新的块
    if (freeCount == 0) {
        // 判定输赢 1空白为0 2上下左右是否还能移动
        for (int r = 0; r < GAME_ROWS ; r++) {
            for (int c = 0; c < GAME_COLS; c++) {
                //地r行 第c列的数值
                int num = m_allTiled.at(m_iMap[r][c] - 1)->getNumber();
                int objNum = 0;
                //上
                if (c + 1 < GAME_COLS) {
                    objNum = m_allTiled.at(m_iMap[r][c + 1] - 1)->getNumber();
                    // 有一个相等的就不死亡
                    if (num == objNum) {
                        return;
                    }
                }
                //下
                if (c - 1 >= 0) {
                    objNum = m_allTiled.at(m_iMap[r][c - 1] - 1)->getNumber();
                    // 有一个相等的就不死亡
                    if (num == objNum) {
                        return;
                    }
                }
                //左
                if (r - 1 >= 0) {
                    objNum = m_allTiled.at(m_iMap[r - 1][c] - 1)->getNumber();
                    // 有一个相等的就不死亡
                    if (num == objNum) {
                        return;
                    }
                }
                //右
                if (r + 1 < GAME_ROWS) {
                    objNum = m_allTiled.at(m_iMap[r + 1][c] - 1)->getNumber();
                    // 有一个相等的就不死亡
                    if (num == objNum) {
                        return;
                    }
                }
            }
        }
        
        Scene *scene = GameOver::createScene();
        // 动画
        Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5, scene));
        return;
    }
    
    int num = arc4random() % freeCount;
    //num = 5;
    //int num = rand() % freeCount;
    int row = 0;
    int col = 0;
    int count=0;
    // 给随机数在表格中确定位置
    bool find=false;
    for(col = 0; col < GAME_COLS; col++) {
        for (row = 0; row < GAME_ROWS; row++) {
            if(m_iMap[row][col] == 0) {
                // 空白数大于随机数 保证数能有区域
                if(count == num) {
                    find=true;
                    break;
                }
                // 记录空白的数量
                count++;
            }
        }
        if (find) {
            break;
        }
    }
    //位置也放进去
    MovedTiled *tiled= MovedTiled::create(row,col);
    //产生一个块 放入在m_alltiled中
    m_allTiled.pushBack(tiled);
    
    //消除类游戏俄罗斯方块 2048等 都有设置map
    //获取索引值从0开始编号 >0说明有值
    m_iMap[row][col]= (int)m_allTiled.getIndex(tiled) + 1;
    tiled->showAt(row, col);

    mapColor->addChild(tiled);

}

void Game::moveUp()
{
    //移动所有的块
    for(int col = GAME_COLS - 1; col >= 0; col--) {
        //先从第三行移到第四行 再从第二行移到第三行
        for (int row = GAME_ROWS - 1; row >= 0; row--) {
            //判断是否有块需要移动
            if (m_iMap[row][col] > 0) {
                //当前行移动到上一行
                for (int col1 = col; col1 < GAME_ROWS - 1; col1++) {
                    //上方是否空
                    if (m_iMap[row][col1 + 1] == 0) {
                        //上一行的那一列等于当前行的那一列
                        m_iMap[row][col1 + 1] = m_iMap[row][col1];
                        m_iMap[row][col1] = 0;
                        m_allTiled.at(m_iMap[row][col1 + 1] - 1)->moveTo(row, col1 + 1);
                    } else {
                        //判断是否可以消除
                        //它所要移动的前一个块的数字
                        int numObj = m_allTiled.at(m_iMap[row][col1 + 1] - 1)->getNumber();
                        //目前自己的数字
                        int numNow = m_allTiled.at(m_iMap[row][col1] - 1)->getNumber();
                        if (numObj == numNow) {
                            m_iScore += numNow * 2;
                            // 新节点数字乘2
                            m_allTiled.at(m_iMap[row][col1 + 1] - 1)->setNumber(numObj);
                            // 旧节点移除
                            m_allTiled.at(m_iMap[row][col1] - 1)->removeFromParent();
                            // 纠正map中的排序
                            int index = m_iMap[row][col1];
                            //m_iMap[row][col1]从队伍中移除了 后面的节点都减1
                            m_allTiled.erase(m_iMap[row][col1] - 1);
                            for (int r = 0; r < GAME_ROWS; r++) {
                                for (int c = 0; c < GAME_COLS; c++) {
                                    if (m_iMap[r][c] > index) {
                                        // map中大于index的值全部－1
                                        m_iMap[r][c]--;
                                    }
                                }
                            }
                            m_iMap[row][col1] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Game::moveDown()
{
    for(int col = 0; col < GAME_COLS; col++) {
        for (int row = 0; row < GAME_ROWS; row++) {
            if (m_iMap[row][col] > 0) {
                for (int col1 = col; col1 > 0; col1--) {
                    if (m_iMap[row][col1 - 1] == 0) {
                        m_iMap[row][col1 - 1] = m_iMap[row][col1];
                        m_iMap[row][col1] = 0;
                        m_allTiled.at(m_iMap[row][col1 - 1] - 1)->moveTo(row, col1 - 1);
                    } else {
                        int numObj = m_allTiled.at(m_iMap[row][col1 - 1] - 1)->getNumber();
                        int numNow = m_allTiled.at(m_iMap[row][col1] - 1)->getNumber();
                        if (numObj == numNow) {
                            m_iScore += numNow * 2;
                            m_allTiled.at(m_iMap[row][col1 - 1] - 1)->setNumber(numObj);
                            m_allTiled.at(m_iMap[row][col1] - 1)->removeFromParent();
                            int index = m_iMap[row][col1];
                            m_allTiled.erase(m_iMap[row][col1] - 1);
                            for (int r = 0; r < GAME_ROWS; r++) {
                                for (int c = 0; c < GAME_COLS; c++) {
                                    if (m_iMap[r][c] > index) {
                                        m_iMap[r][c]--;
                                    }
                                }
                            }
                            m_iMap[row][col1] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Game::moveLeft()
{
    for(int col = 0; col < GAME_COLS; col++) {
        for (int row = 0; row < GAME_ROWS; row++) {
            if (m_iMap[row][col] > 0) {
                for (int row1 = row; row1 > 0; row1--) {
                    if (m_iMap[row1 - 1][col] == 0) {
                        m_iMap[row1 - 1][col] = m_iMap[row1][col];
                        m_iMap[row1][col] = 0;
                        m_allTiled.at(m_iMap[row1 - 1][col]-1)->moveTo(row1 - 1, col);
                    } else {
                        int numObj = m_allTiled.at(m_iMap[row1 - 1][col] - 1)->getNumber();
                        int numNow = m_allTiled.at(m_iMap[row1][col] - 1)->getNumber();
                        if (numObj == numNow) {
                            m_iScore += numNow * 2;
                            m_allTiled.at(m_iMap[row1 - 1][col] - 1)->setNumber(numObj);
                            m_allTiled.at(m_iMap[row1][col] - 1)->removeFromParent();
                            int index = m_iMap[row1][col];
                            m_allTiled.erase(m_iMap[row1][col] - 1);
                            for (int r = 0; r < GAME_ROWS; r++) {
                                for (int c = 0; c < GAME_COLS; c++) {
                                    if (m_iMap[r][c] > index) {
                                        m_iMap[r][c]--;
                                    }
                                }
                            }
                            m_iMap[row1][col] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Game::moveRight()
{
    for(int col = 0; col < GAME_COLS; col++) {
        for (int row = GAME_ROWS - 1; row >= 0; row--) {
            if (m_iMap[row][col] > 0) {
                for (int row1 = row; row1 < GAME_ROWS - 1; row1++) {
                    if (m_iMap[row1 + 1][col] == 0) {
                        m_iMap[row1 + 1][col] = m_iMap[row1][col];
                        m_iMap[row1][col] = 0;
                        m_allTiled.at(m_iMap[row1 + 1][col]-1)->moveTo(row1 + 1, col);
                    } else {
                        int numObj = m_allTiled.at(m_iMap[row1 + 1][col] - 1)->getNumber();
                        int numNow = m_allTiled.at(m_iMap[row1][col] - 1)->getNumber();
                        if (numObj == numNow) {
                            m_iScore += numNow * 2;
                            m_allTiled.at(m_iMap[row1 + 1][col] - 1)->setNumber(numObj);
                            m_allTiled.at(m_iMap[row1][col] - 1)->removeFromParent();
                            int index = m_iMap[row1][col];
                            m_allTiled.erase(m_iMap[row1][col] - 1);
                            for (int r = 0; r < GAME_ROWS; r++) {
                                for (int c = 0; c < GAME_COLS; c++) {
                                    if (m_iMap[r][c] > index) {
                                        m_iMap[r][c]--;
                                    }
                                }
                            }
                            m_iMap[row1][col] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }
}
