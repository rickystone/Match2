//
//  mainEnter.cpp
//  Match
//
//  Created by ricky stone on 14-2-9.
//
//

#include "mainEnter.h"
#include "PropBuyUI.h"
#include "match.h"
#include "Logo.h"

#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

Scene* mainEnter::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = mainEnter::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

mainEnter::mainEnter()
{}

mainEnter::~mainEnter()
{}

void mainEnter::setupJson()
{
    Layer* uiLayer = Layer::create();
    Layout *myLayout = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UI/daojulan.json"));
    uiLayer->addChild(myLayout);
    this->addChild(uiLayer);
}

bool mainEnter::init()
{
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }
    
    //setupJson();
    setupBackGround();
    setupButton();
    
    //注册回调
    return true;
}

void mainEnter::previousCallback(Object* sender, TouchEventType type)
{
    CCLOG("fuck previouscallback\n");
    auto s = Director::getInstance()->getWinSize();
    int x =  CCRANDOM_0_1()*s.width-1;
    int y =  CCRANDOM_0_1()*s.height-1;
    auto sprite = Sprite::create("Icon.png");
    addChild(sprite);
    sprite->setPosition(Point(x,y));
}


void mainEnter::setupBackGround()
{
    auto s = Director::getInstance()->getWinSize();
    auto layer = LayerColor::create(Color4B(100, 100, 100, 255), s.width, s.height);
    layer->setCascadeColorEnabled(false);
    this->addChild(layer);
}

void mainEnter::setupButton()
{
    auto s = Director::getInstance()->getWinSize();
    Button* button = Button::create();
    button->setTouchEnabled(true);
    button->loadTextures("backtotopnormal.png", "backtotoppressed.png", "");
    button->setPosition(Point(s.width/2,s.height/2));
    button->addTouchEventListener(this, toucheventselector(mainEnter::touchEvent));
    addChild(button);
    
    //setup label
    TTFConfig ttfConfig("fonts/arial.ttf", 20, GlyphCollection::DYNAMIC,nullptr,true);
    auto label = Label::createWithTTF(ttfConfig,"Play",TextHAlignment::CENTER,s.width);
    label->setColor( Color3B::WHITE );
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button->getVirtualRenderer()->addChild(label);
    label->setPosition(Point(button->getContentSize().width/2, button->getContentSize().height/2));
}

void mainEnter::touchEvent(Object *pSender, TouchEventType type)
{
    switch (type)
    {
        case gui::TOUCH_EVENT_BEGAN:
            CCLOG("GUI TOUCH EVENT BEGAN");
            break;
            
        case gui::TOUCH_EVENT_MOVED:
            CCLOG("GUI TOUCH EVENT MOVED");
            break;
            
        case gui::TOUCH_EVENT_ENDED:
            CCLOG("GUI TOUCH EVENT ENDED");
            playScene();
            break;
            
        case gui::TOUCH_EVENT_CANCELED:
            break;
            
        default:
            break;
    }
}

void mainEnter::playScene()
{
    float duration = 0.5f;
    auto layer = Logo::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}


