//
//  pauseLayer.h
//  Match
//
//  Created by 程小二 on 14-2-11.
//
//

#ifndef Match_pauseLayer_h
#define Match_pauseLayer_h

#include "cocos2d.h"
#include "gui/CocosGUI.h"

USING_NS_CC;
using namespace gui;

class PauseLayer: public LayerColor
{
    
public:
    PauseLayer();
    ~PauseLayer();
    
    bool init();
    
    //implement the "static create()" method manually
    CREATE_FUNC(PauseLayer);
    
    static Scene* scene(RenderTexture* sqr,bool isFlip);
    
    void setupButton();
    void restartEvent(cocos2d::Object *pSender, TouchEventType type);
    void continueEvent(cocos2d::Object *pSender, TouchEventType type);
    void backtoMainMenuEvent(cocos2d::Object *pSender, TouchEventType type);

public:
    virtual void onEnter();
	virtual void onExit();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    Scene *mGameScene;
};

#endif
