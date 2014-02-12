//
//  mainEnter.h
//  Match
//
//  Created by ricky stone on 14-2-9.
//
//

#ifndef Match_mainEnter_h
#define Match_mainEnter_h

#include "cocos2d.h"
USING_NS_CC;

#include "gui/CocosGUI.h"

//USING_NS_CC;
using namespace gui;


class mainEnter :  public cocos2d::Layer
{
public:
    mainEnter();
    ~mainEnter();
    
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(mainEnter);
    bool init();
    
private:
    void setupBackGround();
    void setupButton();
    void touchEvent(Object *pSender, TouchEventType type);
    void playScene();
};

#endif
