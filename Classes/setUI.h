//
//  setUI.h
//  Match
//
//  Created by 程小二 on 14-3-16.
//
//

#ifndef Match_setUI_h
#define Match_setUI_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"
using namespace gui;

class setUI : public Layer
{
public:
    setUI();
    ~setUI();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(setUI);
    
    bool init();
    
private:
    void setup();
    void backButtonEvent(cocos2d::Object *pSender, TouchEventType type);
};

#endif
