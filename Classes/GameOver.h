//
//  GameOver.h
//  2048
//
//  Created by CTC on 15/7/20.
//
//

#ifndef GameOver_h
#define GameOver_h

#include "cocos2d.h"
USING_NS_CC;
class GameOver : public Layer {
public :
    static Scene *createScene();
    CREATE_FUNC(GameOver);
    virtual bool init();
    void menuRestartCallBack(Ref *pObject);
};


#endif /* GameOver_h */
