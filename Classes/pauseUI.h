//
//  pauseUI.h
//  Match
//
//  Created by 程小二 on 14-3-14.
//
//

#ifndef Match_pauseUI_h
#define Match_pauseUI_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"

using namespace gui;

class pauseUI : public Layer
{
public:
    pauseUI();
    ~pauseUI();
    CREATE_FUNC(pauseUI);
    bool init();
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    virtual void onEnter();
    virtual void onExit();

    
private:
    void continueButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void restartButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void backMainUIButtonEvent(cocos2d::Object *pSender, TouchEventType type);
};

#endif
