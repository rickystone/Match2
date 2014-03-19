//
//  timeOver.h
//  Match
//
//  Created by 程小二 on 14-3-11.
//
//

#ifndef Match_timeOver_h
#define Match_timeOver_h

#include "cocos2d.h"
using namespace cocos2d;

class timeOver : public Layer
{
public:
    timeOver();
    ~timeOver();
    
    static timeOver* create();
    
    bool init();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void burnPic1(const char* sprieFileName);
    void burnPic2(const char* sprieFileName);
};

#endif
