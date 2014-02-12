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
        setupButton();
        
        /*
        auto s = Director::getInstance()->getWinSize();
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/seamaid.plist","animations/seamaid.png");
        Sprite* plistSprite = Sprite::createWithSpriteFrameName("fish12_catch_01.png");
        Vector<SpriteFrame*> cc;
        char name[20];
        for(int i=0; i<4; i++)
        {
            sprintf(name,"fish11_catch_0%d.png",i+1);
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
            cc.pushBack(frame);
        }
        
        Animation* plistAnimation = Animation::createWithSpriteFrames(cc,0.15f);
        Animate* plistAnimate = Animate::create(plistAnimation);
        plistSprite->runAction(CCRepeatForever::create(plistAnimate));
        addChild(plistSprite);
        plistSprite->setPosition(Point(s.width/2,s.height/2));*/
        
    } while (0);
    
    return ret;
}

void PauseLayer::onEnter()
{
    LayerColor::onEnter();
    // Register Touch Event
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

Scene *PauseLayer::scene(RenderTexture* sqr, bool isFlip)
{
	Scene *sc = NULL;
	do{
		sc = Scene::create();
		CC_BREAK_IF(!sc);
        
		/*Size size = Director::getInstance()->getWinSize();
		Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
		_spr->setPosition(Point(size.width/2, size.height/2));
		_spr->setFlippedY(true);
		_spr->setColor(Color3B::GRAY);
		sc->addChild(_spr);*/
        
		PauseLayer *layer = PauseLayer::create();
		CC_BREAK_IF(!layer);
		sc->addChild(layer);
        
	}while(0);
	return sc;
}

void PauseLayer::setupButton()
{
    const char* normal = "backtotopnormal.png";
    const char* pressed  = "backtotoppressed.png";
    
    //restart btn
    Button *restart_btn = AnimationUtil::createButton(normal, pressed);
    restart_btn->addTouchEventListener(this, toucheventselector(PauseLayer::restartEvent));
    addChild(restart_btn);
    
    Label* restart_label = AnimationUtil::createLabel("fonts/arial.ttf", 30);
    restart_label->setString("restartGame");
    restart_btn->getVirtualRenderer()->addChild(restart_label);
    restart_label->setPosition(Point(restart_btn->getContentSize().width/2, restart_btn->getContentSize().height/2));
    
    //continue btn
    Button* continue_btn =AnimationUtil::createButton(normal, pressed);
    continue_btn->addTouchEventListener(this, toucheventselector(PauseLayer::continueEvent));
    addChild(continue_btn);
    
    Label* continue_label = AnimationUtil::createLabel("fonts/arial.ttf", 30);
    continue_label->setString("continueGame");
    continue_btn->getVirtualRenderer()->addChild(continue_label);
    continue_label->setPosition(Point(continue_btn->getContentSize().width/2, continue_btn->getContentSize().height/2));
    
    //back to mainMenu
    Button* backto_btn = AnimationUtil::createButton(normal, pressed);
    backto_btn->addTouchEventListener(this, toucheventselector(PauseLayer::backtoMainMenuEvent));
    addChild(backto_btn);
    
    Label* backto_label = AnimationUtil::createLabel("fonts/arial.ttf", 30);
    backto_label->setString("backToMainMenu");
    backto_btn->getVirtualRenderer()->addChild(backto_label);
    backto_label->setPosition(Point(backto_btn->getContentSize().width/2, backto_btn->getContentSize().height/2));

    
    auto s = Director::getInstance()->getWinSize();
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



