//
//  MovedTiled.cpp
//  2048
//
//  Created by CTC on 15/7/17.
//
//

#include <stdio.h>
#include "MovedTiled.h"

//void MovedTiled::setRow(int row)
//{
//    m_iRow = row;
//}
//
//int MovedTiled::getRow()
//{
//    return m_iRow;
//}
//
//void MovedTiled::setCol(int col)
//{
//    m_iCol = col;
//}
//
//int MovedTiled::getCol()
//{
//    return m_iCol;
//}
//


MovedTiled *MovedTiled::create(int r, int c)
{
    MovedTiled *pRet = new MovedTiled(r, c);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

MovedTiled::MovedTiled(int r, int c)
{
    m_iRow = r;
    m_iCol = c;
}

MovedTiled::~MovedTiled(){
    
}

bool MovedTiled::init()
{
    if (!Node::init()) {
        return false;
    }
    // 背景层
    LayerColor *bkColor = LayerColor::create(Color4B(200, 200, 200, 255), GAME_TILED_WIDTH, GAME_TILED_WIDTH);
    this->addChild(bkColor);
    bkColor->setTag(110);
    
    // 数字层 产生随机数0-9
    int n = rand() % 10;
    // 数字>0产生2 ＝0产生4 2和4出现比例9:1
    this->m_iNumber = n > 0 ? 2 : 4;
    Label *label = Label::createWithSystemFont(StringUtils::format("%d", this->m_iNumber), "Arial", 60);
    switch (m_iNumber) {
        case 2:
            bkColor->setColor(Color3B(230,220,210));
            break;
            
        case 4:
            bkColor->setColor(Color3B(230,210,190));
            break;
            
        default:
            break;
    }
    // 将数字转成label 设置位置
    // label->setScale(4);放大之后失真
    label->setColor(Color3B::BLACK);
    label->setPosition(Point(GAME_TILED_WIDTH / 2, GAME_TILED_WIDTH / 2));
    bkColor->addChild(label);
    label->setTag(10);
    
    return true;
}

int MovedTiled::getNumber()
{
    return m_iNumber;
}

//重复值相加
void MovedTiled::setNumber(int number)
{
    m_iNumber = 2 * number;
    auto bkColor = this->getChildByTag(110);
    Label *label = (Label *)bkColor->getChildByTag(10);
    label->setString(StringUtils::format("%d", m_iNumber));
    // 动画效果 从大到小 再从小到大
    bkColor->runAction(Sequence::create(ScaleTo::create(0.2, 0.8), ScaleTo::create(0.2, 1.2), ScaleTo::create(0.2, 1.0), NULL));
    switch (m_iNumber) {
        case 2:
            bkColor->setColor(Color3B(230,220,210));
        case 4:
            bkColor->setColor(Color3B(230,210,190));
            break;
        case 8:
            bkColor->setColor(Color3B(230,150,100));
            label->setColor(Color3B(255,255,255));
            break;
        case 16:
            bkColor->setColor(Color3B(230,120,80));
            label->setColor(Color3B(255,255,255));
            break;
        case 32:
            bkColor->setColor(Color3B(230,100,90));
            label->setColor(Color3B(255,255,255));
            break;
        case 64:
            bkColor->setColor(Color3B(230,70,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 128:
            bkColor->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 256:
            bkColor->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 512:
            bkColor->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 1024:
        case 2048:
            label->setScale(0.5);
            bkColor->setColor(Color3B(210,180,30));
            label->setColor(Color3B(255,255,255));
    }
}

void MovedTiled::moveTo(int r, int c)
{
    this->m_iRow = r;
    this->m_iCol = c;
    // 位置相对于mapColor
    this->setPosition(Point(GAME_TILED_WIDTH * m_iRow + GAME_TILED_BOARD_WIDTH* (m_iRow + 1), GAME_TILED_WIDTH * m_iCol + GAME_TILED_BOARD_WIDTH * (m_iCol + 1)));
}

void MovedTiled::showAt(int r, int c)
{
    moveTo(r, c);
    //动画效果
    auto bkColor = this->getChildByTag(110);
    // 从大到小 再从小到大
    bkColor->runAction(Sequence::create(ScaleTo::create(0.2, 0.8), ScaleTo::create(0.2, 1.2), ScaleTo::create(0.2, 1.0), NULL));
}