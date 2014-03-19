//
//  readyGo.cpp
//  Match
//
//  Created by 程小二 on 14-3-11.
//
//

#include "readyGo.h"

readyGo::readyGo() {}

readyGo::~readyGo() {}

readyGo* readyGo::create()
{
    readyGo *pret = new readyGo;
    pret->init();
    pret->autorelease();
    return pret;
}

bool readyGo::init()
{
    setupStuff();
    return true;
}

void readyGo::setupStuff()
{
    auto layer = LayerColor::create(Color4B(100,100,100,10));
    addChild(layer);
    
    auto func1 = CallFunc::create( std::bind(&readyGo::burnPic, this, "readyGo/daojs_1.png"));
    auto func2 = CallFunc::create( std::bind(&readyGo::burnPic, this, "readyGo/daojs_2.png"));
    auto func3 = CallFunc::create( std::bind(&readyGo::burnPic, this, "readyGo/daojs_3.png"));
    auto funcGo = CallFunc::create( std::bind(&readyGo::burnPic, this, "readyGo/daojs_go.png"));
    
    this->runAction(Sequence::create(func1, DelayTime::create(1.0f),
                                     func2, DelayTime::create(1.0f),
                                     func3, DelayTime::create(1.0f),
                                     funcGo,DelayTime::create(1.0f),RemoveSelf::create(), NULL));
}

void readyGo::burnPic(const char* sprieFileName)
{
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create(sprieFileName);
    addChild(sprite);
    sprite->setPosition(Point(s.width/2, s.height/2));
    
    sprite->setScale(0.1);
    sprite->runAction(Sequence::create(ScaleTo::create(0.5f, 1.0f),
                                       FadeOut::create(0.5f),
                                       RemoveSelf::create(), NULL));
}

void readyGo::onEnter()
{
    Layer::onEnter();
    //Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(readyGo::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(readyGo::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(readyGo::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void readyGo::onExit()
{
    Layer::onExit();
}

bool readyGo::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void readyGo::onTouchMoved(Touch* touch, Event* event)
{
    return;
}

void readyGo::onTouchEnded(Touch* touch, Event* event)
{
    return;
}



