//
//  mainUI.cpp
//  Match
//
//  Created by 程小二 on 14-3-15.
//
//

#include "mainUI.h"
#include "PropBuyUI.h"
#include "BOXUI.h"
#include "monsterAtlas.h"
#include "setUI.h"

Scene* mainUI::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = mainUI::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

mainUI::mainUI()  {}

mainUI::~mainUI() {}

bool mainUI::init()
{
    // Create the imageview
    auto s = Director::getInstance()->getWinSize();
    
    ImageView* back = ImageView::create();
    back->setScale9Enabled(true);
    back->loadTexture("UI/beijing-s9.png");
    back->setSize(Size(s.width, s.height));
    back->setPosition(Point(s.width/2,s.height/2));
    this->addChild(back);
    
    setuptop();
    setupbottom();
    return true;
}

void mainUI::setupbottom()
{
    //setup background
    auto s = Director::getInstance()->getWinSize();
    const char* normal =  "UI/button_01.png";
    const char* pressed = "UI/button_02.png";
    
    //图鉴
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("图鉴");
    alert->setFontName("Marker Felt");
    alert->setColor(Color3B::BLACK);
    alert->setFontSize(30);
    
    // Create the button
    Button* atlas = Button::create();
    atlas->setTouchEnabled(true);
    // open scale9 render
    atlas->setScale9Enabled(true);
    atlas->loadTextures(normal, pressed, "");
    atlas->setSize(Size(atlas->getContentSize().width*2.2, atlas->getContentSize().height*1.5));
    atlas->addChild(alert);
    atlas->addTouchEventListener(this, toucheventselector(mainUI::atlasButtonEvent));
    this->addChild(atlas);
    
    
    atlas->setPosition(Point(atlas->getSize().width/2+15, atlas->getSize().height/2+20));
    Point lastPt = atlas->getPosition();
    
    //开始
    alert = gui::Text::create();
    alert->setText("开始");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    
    // Create the button
    Button *startBtn = Button::create();
    startBtn->setTouchEnabled(true);
    // open scale9 render
    startBtn->setScale9Enabled(true);
    startBtn->loadTextures(normal, pressed, "");
    startBtn->setSize(Size(startBtn->getContentSize().width*3, startBtn->getContentSize().height*1.5));
    startBtn->addChild(alert);
    startBtn->addTouchEventListener(this, toucheventselector(mainUI::startButtonEvent));
    this->addChild(startBtn);
    startBtn->setPosition(Point(atlas->getPosition().x + atlas->getSize().width/2 + 10 + startBtn->getSize().width/2, lastPt.y));
    
    
    lastPt = startBtn->getPosition();
    
    //魔法石
    alert = gui::Text::create();
    alert->setText("魔法石");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    
    // Create the button
    Button *stoneBtn = Button::create();
    stoneBtn->setTouchEnabled(true);
    // open scale9 render
    stoneBtn->setScale9Enabled(true);
    stoneBtn->loadTextures(normal, pressed, "");
    stoneBtn->setSize(Size(stoneBtn->getContentSize().width*2.2, stoneBtn->getContentSize().height*1.5));
    stoneBtn->addChild(alert);
    stoneBtn->addTouchEventListener(this, toucheventselector(mainUI::magicStoneButtonEvent));
    this->addChild(stoneBtn);
    stoneBtn->setPosition(Point(startBtn->getPosition().x + startBtn->getSize().width/2 + 10 + stoneBtn->getSize().width/2,
                                lastPt.y));
}

void mainUI::setuptop()
{
    auto s = Director::getInstance()->getWinSize();
    //金钱
    ImageView *moneyView = ImageView::create();
    moneyView->setScale9Enabled(true);
    moneyView->loadTexture("UI/dipang.png");
    moneyView->setSize(Size(s.width*0.35, 50));
    addChild(moneyView);
    moneyView->setPosition(Point(moneyView->getSize().width/2 + 20, s.height - moneyView->getSize().height/2 - 10));
    
    
    gui::Text* alert = gui::Text::create();
    alert->setText("金钱999999");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    moneyView->addChild(alert);
    
    //+
    Button* addBtn = Button::create();
    addBtn->setTouchEnabled(true);
    //addBtn->setScale9Enabled(true);
    addBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    //addBtn->setSize(Size(s.width/10, s.width/12));
    addBtn->addTouchEventListener(this, toucheventselector(mainUI::coinButtonEvent));
    addChild(addBtn);
    addBtn->setPosition(Point(moneyView->getPosition().x + moneyView->getSize().width/2 + 10 + addBtn->getSize().width/2,
                              moneyView->getPosition().y));
    //宝石
    ImageView *dimandView = ImageView::create();
    dimandView->setScale9Enabled(true);
    dimandView->loadTexture("UI/dipang.png");
    dimandView->setSize(Size(s.width*0.35, 50));
    addChild(dimandView);
    dimandView->setPosition(Point(addBtn->getPosition().x + addBtn->getSize().width/2 + 10 + dimandView->getSize().width/2,
                                  addBtn->getPosition().y));
    
    alert = gui::Text::create();
    alert->setText("宝石999999");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    dimandView->addChild(alert);
    
    //+
    Button* baoshiBtn = Button::create();
    baoshiBtn->setTouchEnabled(true);
    //baoshiBtn->setScale9Enabled(true);
    baoshiBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    //baoshiBtn->setSize(Size(s.width/10, s.width/12));
    baoshiBtn->addTouchEventListener(this, toucheventselector(mainUI::dimandButtonEvent));
    addChild(baoshiBtn);
    baoshiBtn->setPosition(Point(dimandView->getPosition().x + dimandView->getSize().width/2 + 10 + baoshiBtn->getSize().width/2,
                                 dimandView->getPosition().y));
    
    //setup red star
    ImageView *starBkView = ImageView::create();
    starBkView->setScale9Enabled(true);
    starBkView->loadTexture("UI/dipang.png");
    starBkView->setSize(Size(s.width*0.45, 50));
    addChild(starBkView);
    starBkView->setPosition(Point(starBkView->getSize().width/2 + 20,
                                  baoshiBtn->getPosition().y - baoshiBtn->getSize().height/2 - starBkView->getSize().height/2 - 10));
    
    ImageView* star1 = ImageView::create();
    star1->loadTexture("UI/aixin.png");
    starBkView->addChild(star1);
    star1->setPosition(Point(-starBkView->getSize().width/2 + star1->getSize().width/2 + 5, -5));
    
    ImageView* star2 = ImageView::create();
    star2->loadTexture("UI/aixin.png");
    starBkView->addChild(star2);
    star2->setPosition(Point(star1->getPosition().x + star1->getSize().width + 2, -5));
    
    ImageView* star3 = ImageView::create();
    star3->loadTexture("UI/aixin.png");
    starBkView->addChild(star3);
    star3->setPosition(Point(star2->getPosition().x + star2->getSize().width + 2, -5));
    
    ImageView* star4 = ImageView::create();
    star4->loadTexture("UI/aixin.png");
    starBkView->addChild(star4);
    star4->setPosition(Point(star3->getPosition().x + star3->getSize().width + 2, -5));
    
    ImageView* star5 = ImageView::create();
    star5->loadTexture("UI/aixin.png");
    starBkView->addChild(star5);
    star5->setPosition(Point(star4->getPosition().x + star4->getSize().width + 2, -5));
    
    //设置
    Button* setupBtn = Button::create();
    setupBtn->setTouchEnabled(true);
    //setupBtn->setScale9Enabled(true);
    setupBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    //setupBtn->setSize(Size(s.width/10, s.width/12));
    setupBtn->addTouchEventListener(this, toucheventselector(mainUI::setupButtonEvent));
    addChild(setupBtn);
    setupBtn->setPosition(Point(s.width - setupBtn->getSize().width/2 - 10, starBkView->getPosition().y));
    
    alert = gui::Text::create();
    alert->setText("设置");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    setupBtn->addChild(alert);

    //box
    Button* boxBtn = Button::create();
    boxBtn->setTouchEnabled(true);
    //boxBtn->setScale9Enabled(true);
    boxBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    //boxBtn->setSize(Size(s.width/10, s.width/12));
    boxBtn->addTouchEventListener(this, toucheventselector(mainUI::boxButtonEvent));
    addChild(boxBtn);
    boxBtn->setPosition(Point(setupBtn->getPosition().x - setupBtn->getSize().width - 10, starBkView->getPosition().y));
    
    alert = gui::Text::create();
    alert->setText("BOX");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    boxBtn->addChild(alert);
}

void mainUI::atlasButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("atlas button event");
        
        float duration = 0.5f;
        auto layer = monsterAtlas::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void mainUI::startButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("start btn event");
        
        float duration = 0.5f;
        auto layer = PropBuyUI::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void mainUI::magicStoneButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("magic stone btn event");
    }
}

void mainUI::coinButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("coin touch event mainui");
    }
}

void mainUI::dimandButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("dimand touch event mainui");
    }
}

void mainUI::setupButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("setup btn event mainui");
        
        float duration = 0.5f;
        auto layer = setUI::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void mainUI::boxButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("box button event mainui");
        float duration = 0.5f;
        auto layer = BOXUI::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}









