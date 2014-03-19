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
#include "mainEnter.h"
#include "coreMatch.h"
#include "monster.h"
#include "Pet.h"
#include "AnimationUtil.h"
#include "Prop.h"
#include "Attack.h"
#include "readyGo.h"
#include "timeOver.h"
#include "pauseUI.h"

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

bool match::init()
{
    //1.super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    //auto go = readyGo::create();
    //addChild(go,2);
    
    _pCoreMatch = new coreMatch();
    _pCoreMatch->init();
    addChild(_pCoreMatch,1);
    
    //碰撞检测回调
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(match::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //set up back ground
    
    ImageView* bkground = ImageView::create();
    bkground->setScale9Enabled(true);
    bkground->loadTexture("UI/beijing-s9.png");
    bkground->setSize(Size(s.width, s.height));
    bkground->setPosition(Point(s.width/2,s.height/2));
    this->addChild(bkground);

    
    setupTimerProgress();
    //setupEnergyProgress();
    
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("pause");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);

    
    const char* normal = "UI/normal.png";
    const char* pressed = "UI/press.png";
    // Create the button
    Button* button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width, button->getContentSize().height));
    button->setPosition(Point(s.width - button->getContentSize().width/2-10, s.height - button->getContentSize().height/2-10));
    button->addTouchEventListener(this, toucheventselector(match::pauseButtonEvent));
    button->addChild(alert);
    this->addChild(button);
    
    // Create the imageview
    ImageView* imageView = ImageView::create();
    imageView->setScale9Enabled(true);
    imageView->loadTexture("UI/dipang.png");
    imageView->setSize(Size(s.width, 170));
    imageView->setPosition(Point(s.width/2, button->getPosition().y-button->getSize().height/2-imageView->getSize().height/2-5));
    addChild(imageView);
    
    _pMonster = new monster();
    _pMonster->init();
    
    _pPet = new Pet;
    _pPet->init();
    
    addChild(_pMonster,0);
    addChild(_pPet,0);
    _pCoreMatch->setmonster_Pos(_pMonster->getmonster_pos());
    
    scheduleUpdate();
    
    /*
    auto delay = DelayTime::create(4.0f);
    auto callfunc = CallFunc::create(
                               // lambda
                               [&](){
                                   scheduleUpdate();
                               });
    auto seq = Sequence::create(delay,callfunc,NULL);
    this->runAction(seq);(*/
    
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
    //auto emitter = ParticleSystemQuad::create("effect/baoxiang.plist");
    //addChild(emitter);
    //emitter->setPosition(touch->getLocation());
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
        Attack* attack = (Attack*)b1->getNode();
        attack->killMe();
        
        //this->addEneryBar(2);
    }
    return true;
}

void match::continueFromPause()
{
}

void match::setupTimerProgress()
{
    auto s = Director::getInstance()->getWinSize();
    auto back = Sprite::create("UI/tuijintiao1.png");
    addChild(back,0,kTimerBar);
    
    auto xx = Sprite::create("UI/tuijintiao1.png");
    back->setPosition(Point(s.width/2, xx->getContentSize().height/2));
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("UI/tuijintiao2.png");
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
    auto back = Sprite::create("UI/tuijintiao1.png");
    addChild(back,0,kEnergyBar);
    
    auto xx = Sprite::create("UI/tuijintiao1.png");
    back->setPosition(Point(s.width/2, s.height-xx->getContentSize().height/2));
    
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("UI/tuijintiao2.png");
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
    _pCoreMatch->playClearAccount();
}

void match::pauseButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    pauseUI *pret = pauseUI::create();
    addChild(pret,10);
    unscheduleUpdate();
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
            unscheduleUpdate();
            
            auto a1 = CallFunc::create(
                             // lambda
                             [&](){
                                 //定义一个弹出层，传入一张背景图
                                 auto over = timeOver::create();
                                 this->addChild(over,100);
                                 _pCoreMatch->playBoxesSmile();
                             });
            
            auto a2 =CallFunc::create(
                                      // lambda
                                      [&](){
                                          _pCoreMatch->playClearAccount();
                                      });
            
            auto seq  = Sequence::create(a1, DelayTime::create(4.0f), a2, NULL);
            this->runAction(seq);
        }
    }
}




