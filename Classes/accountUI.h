//
//  accountUI.h
//  Match
//
//  Created by 程小二 on 14-3-16.
//
//

#ifndef Match_accountUI_h
#define Match_accountUI_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"
using namespace gui;

class accountUI : public Layer
{
public:
    accountUI();
    ~accountUI();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(accountUI);
    
    bool init();
    
private:
    void setup();
    void repeatButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void backToMainUIButtonEvent(cocos2d::Object *pSender, TouchEventType type);

};



#endif
