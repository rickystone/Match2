//
//  match.cpp
//  MyGame
//
//  Created by ricky stone on 14-1-15.
//
//

#include "match.h"
#include "CCSprite.h"
#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ShaderSprite.h"
#include "PopupLayer.h"
#include "mainEnter.h"
#include "pauseLayer.h"
#include "coreMatch.h"
#include "monster.h"
#include "Pet.h"
#include "AnimationUtil.h"

using namespace cocostudio;

USING_NS_CC_EXT;
USING_NS_CC;


//136 4687 5031  住－固态硬盘。

Scene* match::createScene()
{
    //'scene' is an autorelease object
    //add physicals
    auto scene = Scene::createWithPhysics();
    //DrawMask参数可以选择打开绘制哪些部分比如，Joint、Shape、Contact等等
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->getPhysicsWorld()->setGravity(Point(0,-10));
    //'layer' is an autorelease object
    auto layer = match::create();
    //将这个World传到Layer中。所以我们在HelloWorld类中加入一个函数。将这个world存起来。
    layer->setPhyWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    //return the scene
    return scene;
}

match::match()
:_pCoreMatch(nullptr),
 _pMonster(nullptr),
 _pPet(nullptr),
 _updateBarTime(0.0f),
 _timeBarPercent(100.0f),
 _timeBarLabelNum(60),
 _energyBarPercent(0),
 _energyBarLabelNum(0)

{}

match::~match()
{
    CC_SAFE_RELEASE_NULL(_pCoreMatch);
    CC_SAFE_RELEASE_NULL(_pMonster);
    CC_SAFE_RELEASE_NULL(_pPet);
}

void match::update(float delta)
{
    _updateBarTime += delta;
    if(_updateBarTime >= 1.0)
    {
        _updateBarTime = 0.0f;
        _timeBarPercent -= 1.0f*100/60;
        _timeBarLabelNum -= 1;
        
        auto back = (Sprite*)this->getChildByTag(kTimerBar);
        auto loadingbar = (LoadingBar*)back->getChildByTag(0);
        auto label = (Label*)back->getChildByTag(1);
        
        char buf[10];
        sprintf(buf, "%d\n", _timeBarLabelNum);
        label->setString(buf);
        loadingbar->setPercent(_timeBarPercent);
        
        if(_timeBarLabelNum <= 0)
        {
            //popupLayer();
            //unscheduleUpdate();
        }
    }

}

bool match::init()
{
    //1.super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _pCoreMatch = new coreMatch();
    _pCoreMatch->init();
    
    _pMonster = new monster();
    _pMonster->init();
    
    _pPet = new Pet;
    _pPet->init();
    
    
    addChild(_pCoreMatch,1);
    addChild(_pMonster);
    addChild(_pPet);
    
    _pCoreMatch->setmonster_Pos(_pMonster->getmonster_pos());
    
    //碰撞检测回调
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(match::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    scheduleUpdate();
    
    //set up back ground
    auto bkground = Sprite::create("UI/ui2_r3_c1.png");
    addChild(bkground,-1,kFirstBack);
    auto s = Director::getInstance()->getWinSize();
    bkground->setPosition(Point(s.width/2,s.height/2));
    
    setupPauseButton();
    
    setupTimerProgress();
    setupEnergyProgress();
    
    return true;
}

void match::onEnter()
{
    Layer::onEnter();
    //Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(match::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(match::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(match::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void match::onExit()
{
    Layer::onExit();
}

bool match::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    return true;
}

void match::onTouchMoved(Touch* touch, Event* event)
{
    CCLOG("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
}

void match::onTouchEnded(Touch* touch, Event* event)
{
    _pCoreMatch->onTouch(touch);
    return;
}

bool match::onContactBegin(EventCustom *event, const PhysicsContact& contact)
{
    auto b1 = (PhysicsBody*)contact.getShapeA()->getBody();
    auto b2 = (PhysicsBody*)contact.getShapeB()->getBody();
    CCLOG("onContactBegin %d, %d", b1->getCollisionBitmask(), b2->getCollisionBitmask());
    if(b1->getCollisionBitmask() != b2->getCollisionBitmask())
    {
        //CCLOG("onContactBegin %d, %d", b1->getCollisionBitmask(), b2->getCollisionBitmask());
        _pMonster->hurt();
        this->addEneryBar(2);
    }
    return true;
}

void match::setupTimerProgress()
{
    auto s = Director::getInstance()->getWinSize();
    auto back = Sprite::create("UI/bar_bk.png");
    addChild(back,0,kTimerBar);
    
    auto xx = Sprite::create("UI/ui2_r25_c1.png");
    back->setPosition(Point(s.width/2, xx->getContentSize().height/2));
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("UI/bar.png");
    loadingBar->setDirection(LoadingBarTypeLeft);
    loadingBar->setPercent(_timeBarPercent);
    back->addChild(loadingBar,0,0);
    loadingBar->setPosition(Point(back->getContentSize().width/2, back->getContentSize().height/2));
    
    //setup label word
    TTFConfig ttfConfig("fonts/arial.ttf", 30, GlyphCollection::DYNAMIC,nullptr,true);
    auto label = Label::createWithTTF(ttfConfig,"",TextHAlignment::CENTER,s.width);
    label->setColor( Color3B::WHITE );
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    back->addChild(label,0,1);
    label->setPosition(Point(back->getContentSize().width/2, back->getContentSize().height/2));
    
    char buf[10];
    sprintf(buf, "%d\n", _timeBarLabelNum);
    label->setString(buf);
}

void match::setupEnergyProgress()
{
    auto s = Director::getInstance()->getWinSize();
    auto back = Sprite::create("UI/bar_bk.png");
    addChild(back,0,kEnergyBar);
    
    auto xx = Sprite::create("UI/ui2_r25_c1.png");
    back->setPosition(Point(s.width/2, s.height-xx->getContentSize().height/2));
    
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("UI/bar.png");
    loadingBar->setDirection(LoadingBarTypeLeft);
    loadingBar->setPercent(_energyBarPercent);
    back->addChild(loadingBar,0,0);
    loadingBar->setPosition(Point(back->getContentSize().width/2, back->getContentSize().height/2));
    
    //setup label word
    TTFConfig ttfConfig("fonts/arial.ttf", 30, GlyphCollection::DYNAMIC,nullptr,true);
    auto label = Label::createWithTTF(ttfConfig,"",TextHAlignment::CENTER,s.width);
    label->setColor( Color3B::WHITE );
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    back->addChild(label,0,1);
    label->setPosition(Point(back->getContentSize().width/2, back->getContentSize().height/2));
    
    char buf[10];
    sprintf(buf, "%d\n", _energyBarLabelNum);
    label->setString(buf);
}

void match::popupLayer()
{
    //定义一个弹出层，传入一张背景图
    PopupLayer* pl = PopupLayer::create("popuplayer/BackGround.png");
    //ContentSize 是可选的设置，可以不设置，如果设置把它当作 9 图缩放
    pl->setContentSize(Size(400, 350));
    pl->setTitle("时间到了");
    pl->setContentText("时间到啦", 20, 60, 250);
    //设置回调函数，回调传回一个 CCNode 以获取 tag 判断点击的按钮
    //这只是作为一种封装实现，如果使用 delegate 那就能够更灵活的控制参数了
    pl->setCallbackFunc(this, callfuncN_selector(match::buttonCallback));
    //添加按钮，设置图片，文字，tag 信息
    pl->addButton("popuplayer/pop_button.png", "popuplayer/pop_button.png", "确定", 0);
    //pl->addButton("popuplayer/pop_button.png", "popuplayer/pop_button.png", "取消", 1);
    //添加到当前层
    this->addChild(pl);
}

void match::setupPauseButton()
{
    const char *normal = "CloseNormal.png";
    const char* pressed = "circle.png";
    
    Button* button = Button::create();
    button->setTouchEnabled(true);
    button->loadTextures(normal, pressed, "");

    auto s = Director::getInstance()->getWinSize();
    this->addChild(button);
    button->setPosition(Point(s.width - button->getContentSize().width,
                              s.height- button->getContentSize().height));
    
    button->addTouchEventListener(this, toucheventselector(match::pauseButtonEvent));
    return;
}

void match::addEneryBar(int percent)
{
    auto back = this->getChildByTag(kEnergyBar);
    auto loadingbar = (LoadingBar*)back->getChildByTag(0);
    auto label = (Label*)back->getChildByTag(1);
    
    int curpercent = loadingbar->getPercent();
    curpercent += percent;
    
    if(curpercent >= 100)
    {
        curpercent -= 100;
        loadingbar->setPercent(curpercent);
        
        char buf[10];
        sprintf(buf, "%d", curpercent);
        label->setString(buf);
        //宠物发动攻击
    }
    else
    {
        loadingbar->setPercent(curpercent);
        char buf[10];
        sprintf(buf, "%d", curpercent);
        label->setString(buf);
    }
    return;
}

void match::buttonCallback(cocos2d::Node *pNode)
{
    CCLOG("button call back. tag: %d", pNode->getTag());
    float duration = 0.5f;
    auto mainScene = mainEnter::createScene();
    auto scene = TransitionFade::create(duration, mainScene, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void match::pauseButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    float duration = 0.5f;
    auto pauseScene = PauseLayer::scene();
    auto scene = TransitionFade::create(duration, pauseScene, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}


