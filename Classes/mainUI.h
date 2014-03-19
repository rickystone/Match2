//
//  mainUI.h
//  Match
//
//  Created by 程小二 on 14-3-15.
//
//

#ifndef Match_mainUI_h
#define Match_mainUI_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"
using namespace gui;

class mainUI : public Layer
{
public:
    mainUI();
    ~mainUI();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(mainUI);
    
    bool init();

private:
    void setuptop();
    void setupbottom();
    
    void coinButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void dimandButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    
    void setupButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void boxButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    
    void atlasButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void startButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void magicStoneButtonEvent(cocos2d::Object *pSender, TouchEventType type);

};




#endif
