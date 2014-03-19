//
//  readyGo.h
//  Match
//
//  Created by 程小二 on 14-3-11.
//
//

#ifndef Match_readyGo_h
#define Match_readyGo_h

#include "cocos2d.h"
using namespace cocos2d;

class readyGo : public Layer
{
public:
    readyGo();
    ~readyGo();
    static readyGo* create();
    bool init();
    
    void setupStuff();
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void burnPic(const char* sprieFileName);
};


#endif
