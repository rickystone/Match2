//
//  pauseLayer.cpp
//  Match
//
//  Created by 程小二 on 14-2-11.
//
//

#include "pauseLayer.h"
#include "AnimationUtil.h"
#include "mainEnter.h"
#include "match.h"

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF(!LayerColor::initWithColor(Color4B(255, 255, 255, 250)));
        ret = true;
        
        auto back = Sprite::create("UI/pause_bk.png");
        addChild(back);
        auto s = Director::getInstance()->getWinSize();
        back->setPosition(Point(s.width/2,s.height/2));
        
        setupButton(back);
    } while (0);
    
    return ret;
}

void PauseLayer::onEnter()
{
    LayerColor::onEnter();
    
    //Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PauseLayer::onExit()
{
    LayerColor::onExit();
}

bool PauseLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return true;
}

Scene *PauseLayer::scene()
{
	Scene *sc = NULL;
	do{
		sc = Scene::create();
		CC_BREAK_IF(!sc);
        
		PauseLayer *layer = PauseLayer::create();
		CC_BREAK_IF(!layer);
		sc->addChild(layer);
        
	}while(0);
	return sc;
}

void PauseLayer::setupButton(Sprite* parent)
{
    const char* normal = "backtotopnormal.png";
    const char* pressed  = "backtotoppressed.png";
    
    //restart btn
    Button *restart_btn = AnimationUtil::createButton(normal, pressed);
    restart_btn->addTouchEventListener(this, toucheventselector(PauseLayer::restartEvent));
    parent->addChild(restart_btn);
    
    Label* restart_label = AnimationUtil::createLabel("fonts/arial.ttf", 30);
    restart_label->setString("restartGame");
    restart_btn->getVirtualRenderer()->addChild(restart_label);
    restart_label->setPosition(Point(restart_btn->getContentSize().width/2, restart_btn->getContentSize().height/2));
    
    //continue btn
    Button* continue_btn =AnimationUtil::createButton(normal, pressed);
    continue_btn->addTouchEventListener(this, toucheventselector(PauseLayer::continueEvent));
    parent->addChild(continue_btn);
    
    Label* continue_label = AnimationUtil::createLabel("fonts/arial.ttf", 30);
    continue_label->setString("continueGame");
    continue_btn->getVirtualRenderer()->addChild(continue_label);
    continue_label->setPosition(Point(continue_btn->getContentSize().width/2, continue_btn->getContentSize().height/2));
    
    //back to mainMenu
    Button* backto_btn = AnimationUtil::createButton(normal, pressed);
    backto_btn->addTouchEventListener(this, toucheventselector(PauseLayer::backtoMainMenuEvent));
    parent->addChild(backto_btn);
    
    Label* backto_label = AnimationUtil::createLabel("fonts/arial.ttf", 30);
    backto_label->setString("backToMainMenu");
    backto_btn->getVirtualRenderer()->addChild(backto_label);
    backto_label->setPosition(Point(backto_btn->getContentSize().width/2, backto_btn->getContentSize().height/2));

    
    auto s = parent->getContentSize();
    
    restart_btn->setPosition(Point(s.width/2, s.height*0.7));
    
    continue_btn->setPosition(Point(s.width/2,
                                    restart_btn->getPosition().y - restart_btn->getContentSize().height-5));
    
    backto_btn->setPosition(Point(s.width/2,
                                  continue_btn->getPosition().y - continue_btn->getContentSize().height-5));
}

void PauseLayer::restartEvent(cocos2d::Object *pSender, TouchEventType type)
{
    float duration = 0.5f;
    auto matchScene = match::createScene();
    auto scene = TransitionFade::create(duration, matchScene, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void PauseLayer::continueEvent(cocos2d::Object *pSender, TouchEventType type)
{
    Director::getInstance()->popScene();
}

void PauseLayer::backtoMainMenuEvent(cocos2d::Object *pSender, TouchEventType type)
{
    float duration = 0.5f;
    auto mainScene = mainEnter::createScene();
    auto scene = TransitionFade::create(duration, mainScene, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}



