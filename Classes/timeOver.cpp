//
//  timeOver.cpp
//  Match
//
//  Created by 程小二 on 14-3-11.
//
//

#include "timeOver.h"

timeOver::timeOver() {}

timeOver::~timeOver() {}

timeOver* timeOver::create()
{
    timeOver* pret = new timeOver();
    pret->autorelease();
    pret->init();
    return pret;
}

bool timeOver::init()
{
    auto layer = LayerColor::create(Color4B(100,100,100,10));
    addChild(layer);
    
    auto func1 = CallFunc::create( std::bind(&timeOver::burnPic1, this, "readyGo/shijiandao.png"));
    auto func2 = CallFunc::create( std::bind(&timeOver::burnPic2, this, "readyGo/qingsuan.png"));
    
    this->runAction(Sequence::create(func1, DelayTime::create(2.0f),
                                     func2, DelayTime::create(2.0f),
                                     RemoveSelf::create(), NULL));

    return true;
}

void timeOver::burnPic1(const char* sprieFileName)
{
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create(sprieFileName);
    addChild(sprite);
    sprite->setPosition(Point(s.width/2, s.height/2));
    
    sprite->setScale(0.1);
    sprite->runAction(Sequence::create(ScaleTo::create(0.5f, 1.0f),
                                       DelayTime::create(1.0),
                                       FadeOut::create(0.5f),
                                       RemoveSelf::create(), NULL));
}

void timeOver::burnPic2(const char* sprieFileName)
{
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create(sprieFileName);
    addChild(sprite);
    sprite->setPosition(Point(s.width/2, s.height/2));
    
    sprite->setScale(0.1);
    sprite->runAction(Sequence::create(ScaleTo::create(0.5f, 1.0f),
                                       DelayTime::create(1.0f),
                                       FadeOut::create(0.5f),
                                       RemoveSelf::create(), NULL));
}

void timeOver::onEnter()
{
    Layer::onEnter();
    //Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(timeOver::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(timeOver::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(timeOver::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void timeOver::onExit()
{
    Layer::onExit();
}

bool timeOver::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void timeOver::onTouchMoved(Touch* touch, Event* event)
{
    return;
}

void timeOver::onTouchEnded(Touch* touch, Event* event)
{
    return;
}



