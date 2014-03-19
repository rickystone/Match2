//
//  pauseUI.cpp
//  Match
//
//  Created by 程小二 on 14-3-14.
//
//

#include "pauseUI.h"
#include "match.h"
#include "PropBuyUI.h"
#include "mainUI.h"

pauseUI::pauseUI() {}

pauseUI::~pauseUI() {}

bool pauseUI::init()
{
    auto s = Director::getInstance()->getWinSize();
    auto layer = LayerColor::create(Color4B(100,100,100,90));
    addChild(layer);
    
    // Create the imageview
    ImageView* back = ImageView::create();
    back->setScale9Enabled(true);
    back->loadTexture("UI/green_edit.png");
    back->setSize(Size(s.width*0.8, s.height*0.4));
    back->setPosition(Point(s.width/2,s.height/2));
    this->addChild(back);
    
    
    const char* normal = "UI/normal.png";
    const char* pressed = "UI/press.png";
    
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("继续游戏");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);

    // Create the button //继续游戏
    Button* button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*3, button->getContentSize().height));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(pauseUI::continueButtonEvent));
    back->addChild(button);
    button->setPosition(Point(0, back->getSize().height/2 - button->getSize().height));

    
    Point lastPt = button->getPosition();
    
    int step = (back->getSize().height - button->getSize().height*3)/4;
    
    
    // Add the alert
    alert = gui::Text::create();
    alert->setText("重新开始");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    
    // Create the button //继续游戏
    button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*3, button->getContentSize().height));
    button->setPosition(Point(0, lastPt.y - button->getContentSize().height-step));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(pauseUI::restartButtonEvent));
    back->addChild(button);
    
    
    lastPt = button->getPosition();
    
    // Add the alert
    alert = gui::Text::create();
    alert->setText("回主界面");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    
    // Create the button //继续游戏
    button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*3, button->getContentSize().height));
    button->setPosition(Point(0, lastPt.y - button->getContentSize().height-step));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(pauseUI::backMainUIButtonEvent));
    back->addChild(button);
    
    auto scale = ScaleTo::create(1.0f, 1.0f);
    back->setScale(0.0f);
    back->runAction(EaseElasticOut::create(scale, 1.0f));
    return true;
}

void pauseUI::continueButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("continue button event");
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        //write default value
        match* parent = (match*)getParent();
        parent->unscheduleUpdate();
        parent->scheduleUpdate();
        this->removeFromParentAndCleanup(true);
    }
}

void pauseUI::restartButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("restart button event");
    //write default value
    float duration = 0.5f;
    auto layer = PropBuyUI::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void pauseUI::backMainUIButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("backMainUI button event");
    float duration = 0.5f;
    auto layer = mainUI::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void pauseUI::onEnter()
{
    Layer::onEnter();
    //Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(pauseUI::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(pauseUI::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(pauseUI::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void pauseUI::onExit()
{
    Layer::onExit();
}

bool pauseUI::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void pauseUI::onTouchMoved(Touch* touch, Event* event)
{
    return;
}

void pauseUI::onTouchEnded(Touch* touch, Event* event)
{
    return;
}





