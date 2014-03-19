//
//  BOXUI.h
//  Match
//
//  Created by 程小二 on 14-3-16.
//
//

#ifndef Match_BOXUI_h
#define Match_BOXUI_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"
using namespace gui;

class BOXUI : public Layer
{
public:
    BOXUI();
    ~BOXUI();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(BOXUI);
    
    bool init();
    
private:
    void setupPic();
    void backButtonEvent(cocos2d::Object *pSender, TouchEventType type);
};


#endif
