//
//  MovedTiled.h
//  2048
//
//  Created by CTC on 15/7/17.
//
//

#ifndef MovedTiled_h
#define MovedTiled_h

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class MovedTiled : public Node {
//private:
//    int m_iRow;
//    int m_iCol;
//    int m_iNumber;
//    
private:
//    void setRow(int row);
//    int getRow();
//    void setCol(int col);
//    int getCol();


    int m_iRow;
    int m_iCol;
    int m_iNumber;
    
public:
    static MovedTiled *create(int r, int c);
    MovedTiled(int r, int c);
    ~MovedTiled();
    bool init();
    int getNumber();
    void setNumber(int number);
    // 移动到r行 c列
    void moveTo(int r, int c);
    // 在某个位置显示这个块
    void showAt(int r, int c);
};

#endif /* MovedTiled_h */
