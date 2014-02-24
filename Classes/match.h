//
//  match.h
//  MyGame
//
//  Created by ricky stone on 14-1-15.
//
//

#ifndef MyGame_match_h
#define MyGame_match_h

#include "CCLayer.h"

#include "cocos2d.h"
#include "ShaderSprite.h"
#include "gui/CocosGUI.h"
#include "util.h"

USING_NS_CC;
using namespace gui;

class coreMatch;
class monster;
class Pet;

class match : public cocos2d::Layer
{
public:
    match();
    ~match();
    
    //there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    //implement the "static create()" method manually
    CREATE_FUNC(match);
    
    bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    
    
private:
    
    void setupTimerProgress();
    void setupEnergyProgress();
    void setupPauseButton();
    
    void update(float delta);
    void buttonCallback(cocos2d::Node *pNode);
    void popupLayer();

    void addEneryBar(int percent);
    
    //pause button touch event
    void pauseButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    
private:
    PhysicsWorld* m_world;
    bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
    coreMatch* _pCoreMatch;
    monster* _pMonster;
    Pet* _pPet;
    
    float _updateBarTime;
    float _timeBarPercent;
    int _timeBarLabelNum;
    
    float _energyBarPercent;
    int _energyBarLabelNum;
};

#endif
