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

using namespace cocostudio;

USING_NS_CC_EXT;
USING_NS_CC;

#define MOVEDURATION 0.05
#define PARTICLEDURATION 0.2

enum {
    kBoxBk = 0,
    kBoxNode = 1,
    kTimerBar = 2,
    kEneryBar = 3,
    kMonster = 4,
    kMonsterHp = 5,
    kRabbitPet = 6,
};

bool coordCompareLess(const coord& c1, const coord& c2)
{
    return (c1.c < c2.c || (c1.c == c2.c && c1.r > c2.r));
}

Scene* match::createScene()
{
    // 'scene' is an autorelease object
    //add physicals
    auto scene = Scene::createWithPhysics();
    //DrawMask参数可以选择打开绘制哪些部分比如，Joint、Shape、Contact等等
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->getPhysicsWorld()->setGravity(Point(0,-10));
    
    //创建一个边界
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //使用PhysicalsBody的create方法创建自己想要的物体。
    //PHYSICSBODY_MATERIAL_DEFAULT宏表示的是创建的Body的默认材质，3是边线宽度。编译运行我们会看到场景边上有红色的边界。
    
    
    //auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*0.8, visibleSize.height*0.8), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    //body->setDynamic(false);
    //auto edgeNode = Node::create();
    //edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    //edgeNode->setPhysicsBody(body);
    //scene->addChild(edgeNode);
    
    //'layer' is an autorelease object
    auto layer = match::create();
    
    //将这个World传到Layer中。所以我们在HelloWorld类中加入一个函数。将这个world存起来。
    layer->setPhyWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

match::match() :_canbTouch(true),
                _updateTime(0.0f),
                _updateGrayTime(0.0f),
                _updateTipTime(0.0f),
                _updateBarTime(0.0f),
                _timeBarPercent(100.0f),
                _timeBarLabelNum(60),
                _energyBarPercent(0),
                _energyBarLabelNum(0),
                _monster_Pos(-1,-1),
                _pet_Pos(-1,-1),
                _boxbkPos(-1,-1),
                _bShowTip(false),
                _boxParentNode(nullptr)
{}

match::~match()
{
    CC_SAFE_RELEASE_NULL(_boxParentNode);
}


bool match::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    for(int r = 0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            _rc[r][c] = kUnSigned;
            _boxesPos[r][c] = Point(-1,-1);
            _rcSprites[r][c] = nullptr;
        }
    }
    
    auto winsz = Director::getInstance()->getWinSize();
    
    auto sprite = Sprite::create("Icon.png");
    auto size = sprite->getContentSize();

    auto layer = LayerColor::create(Color4B(100, 100, 100, 255), size.width*ROW+30, size.height*COL+20);
    layer->setCascadeColorEnabled(false);
    layer->setPosition( Point(winsz.width/2 -layer->getContentSize().width/2,
                               winsz.height*0.43-layer->getContentSize().height/2));
    this->addChild(layer,0,kBoxBk);
    _boxbkPos = layer->getPosition();
    
    auto node = Node::create();
    addChild(node,0,kBoxNode);
    _boxParentNode = node;
    _boxParentNode->retain();
    
    createBoxes();
    setupEnergyProgress();
    setupTimerProgress();
    setupMonster();
    setupButton();
    setupPets();
    setupPauseButton();
    scheduleUpdate();
    
    //碰撞检测回调
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_2(match::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

void match::createItemBox(int r, int c)
{
    auto sprite = Sprite::create("Icon.png");
    Color3B color3B;
    colorSpriteEnum randomEnum;
    randomColor(color3B,randomEnum);
    sprite->setColor(color3B);
    
    _rc[r][c] = randomEnum;
    _rcSprites[r][c] = sprite;
    
    sprite->setPosition(_boxesPos[r][c]);
    sprite->setTag(r*ROW+c);
    
    _boxParentNode->addChild(sprite);
    return ;
}

void match::createBoxes()
{
    resetCanbeTouch();
    clearMatchTips();
    clearGraySprites();
    //1 2 3 4 5 6 7 6 5 4 3 2 1
    //create 1
    auto sprite = Sprite::create("Icon.png");
    auto size = sprite->getContentSize();
    
    _boxParentNode->removeAllChildrenWithCleanup(true);
    
    std::vector<std::vector<coord>> rcs;
    std::vector<coord> rc;
    
    rc.push_back(coord(0,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(0,1));
    rc.push_back(coord(1,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(0,2));
    rc.push_back(coord(1,1));
    rc.push_back(coord(2,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(0,3));
    rc.push_back(coord(1,2));
    rc.push_back(coord(2,1));
    rc.push_back(coord(3,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(0,4));
    rc.push_back(coord(1,3));
    rc.push_back(coord(2,2));
    rc.push_back(coord(3,1));
    rc.push_back(coord(4,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(0,5));
    rc.push_back(coord(1,4));
    rc.push_back(coord(2,3));
    rc.push_back(coord(3,2));
    rc.push_back(coord(4,1));
    rc.push_back(coord(5,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(0,6));
    rc.push_back(coord(1,5));
    rc.push_back(coord(2,4));
    rc.push_back(coord(3,3));
    rc.push_back(coord(4,2));
    rc.push_back(coord(5,1));
    rc.push_back(coord(6,0));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(6,1));
    rc.push_back(coord(5,2));
    rc.push_back(coord(4,3));
    rc.push_back(coord(3,4));
    rc.push_back(coord(2,5));
    rc.push_back(coord(1,6));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(6,2));
    rc.push_back(coord(5,3));
    rc.push_back(coord(4,4));
    rc.push_back(coord(3,5));
    rc.push_back(coord(2,6));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(6,3));
    rc.push_back(coord(5,4));
    rc.push_back(coord(4,5));
    rc.push_back(coord(3,6));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(6,4));
    rc.push_back(coord(5,5));
    rc.push_back(coord(4,6));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(6,5));
    rc.push_back(coord(5,6));
    rcs.push_back(rc);
    
    rc.clear();
    rc.push_back(coord(6,6));
    rcs.push_back(rc);
    
    auto bk = (Sprite*)this->getChildByTag(kBoxBk);
    Point parentPos = bk->getPosition();
    
    Point start = Point(parentPos.x - size.width/2 + 10, parentPos.y+size.height/2);
    for(int r=0; r<ROW; r++)
    {
        Point prevPt = Point(start.x, start.y + r*sprite->getContentSize().height + 2);
        for(int c=0; c<COL; c++)
        {
            Point pt = Point(prevPt.x + size.width + 2, prevPt.y);
            prevPt = pt;
            _boxesPos[r][c] = pt;
        }
    }
    
    Vector<FiniteTimeAction*> functionVecs;
    
    std::vector<std::vector<coord>>::iterator it = rcs.begin();
    for(; it != rcs.end(); ++it)
    {
        std::vector<coord>::iterator xi = it->begin();
        for(; xi != it->end(); ++xi)
        {
            coord cr = *xi;
            int r = cr.r;
            int c = cr.c;
            
            auto call = CallFunc::create(std::bind(&match::createItemBox,this,r,c));
            auto delay = DelayTime::create(0.01f);
            functionVecs.pushBack(call);
            functionVecs.pushBack(delay);
        }
    }
    
    Sequence* seq = Sequence::create(functionVecs);
    this->runAction(seq);
}

void match::setupGraySprite(int r, int c)
{
    GreyScaleSprite *ss = GreyScaleSprite::createSprite("Icon.png");
    ss->setPosition(_boxesPos[r][c]);
    this->addChild(ss);
    ss->setTag(r*ROW+c);
    _graysprites.pushBack(ss);
    
    Sprite* sprite = _rcSprites[r][c];
    if(sprite)
        sprite->setVisible(false);
}

void match::clearGraySprites()
{
    for(int i=0; i<_graysprites.size(); i++)
    {
        GreyScaleSprite* sp = _graysprites.at(i);
        if(sp){
            int tag = sp->getTag();
            int r = tag / ROW;
            int c = tag % ROW;
            _rcSprites[r][c]->setVisible(true);
            sp->setVisible(false);
            sp->removeFromParentAndCleanup(true);
        }
    }
    _graysprites.clear();
}

void match::detectSprite(cocos2d::Touch *touch)
{
    Point location = touch->getLocation();
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            Sprite* sprite = _rcSprites[r][c];
            if(sprite)
            {
                Point point = sprite->convertToNodeSpace(location);
                auto rect = Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height);
                bool contain = rect.containsPoint(point);
                if(contain)
                {
                    clearGraySprites();
                    std::vector<coord> collections;
                    findSameColorsSprite(r, c, collections);
                    if(collections.size() <= 2)
                    {
                        for(int i=0; i<collections.size(); i++)
                        {
                            coord co = collections[i];
                            int r = co.r;
                            int c = co.c;
                            setupGraySprite(r,c);
                        }
                        resetCanbeTouch();
                        return;
                    }
                    else if(collections.size() >= 3)
                    {
                        clearMatchTips();
                        _bShowTip = true;
                        //std::sort(std::begin(collections), std::end(collections), coordCompareLess );
                        auto boxdead = CallFunc::create( std::bind(&match::boxDeadEffect, this, collections));
                        auto movebox = CallFunc::create( std::bind(&match::moveBoxes, this, collections));
                        auto attackMonster = CallFunc::create( std::bind(&match::attackMonster, this, collections));
                        auto reset = CallFunc::create( std::bind(&match::resetCanbeTouch,this));
                        auto sequence = Sequence::create(boxdead,
                                                         DelayTime::create(0.5f),
                                                         movebox,
                                                         attackMonster,
                                                         DelayTime::create(collections.size()*0.15f),
                                                         CallFunc::create( std::bind(&match::addEneryBar, this, collections.size()*2)),
                                                         DelayTime::create(collections.size()*0.15f),
                                                         reset,
                                                         NULL);
                        this->runAction(sequence);
                        return;
                    }
                }
            }
        }
    }
    resetCanbeTouch();
}

void match::findSameColorsSprite(int r, int c, std::vector<coord>& collection)
{
    colorSpriteEnum curKc = _rc[r][c];
    std::queue<coord> queues;
    coord co;
    co.r = r;
    co.c = c;
    queues.push(co);
    
    collection.push_back(co);
    
    while (queues.size() > 0) {
        coord co = queues.front();
        queues.pop();
        int r = co.r;
        int c = co.c;
        
        processRC(queues, collection, curKc, r-1, c);
        processRC(queues, collection, curKc, r+1, c);
        processRC(queues, collection, curKc, r, c+1);
        processRC(queues, collection, curKc, r, c-1);
    }
}

void match::processRC(std::queue<coord>& queues, std::vector<coord>& collection, colorSpriteEnum curKc, int r, int c)
{
    bool check_bool = checkBundary(r, c);
    if(check_bool)
    {
        coord co;
        co.r = r;
        co.c = c;
        colorSpriteEnum Kc = _rc[r][c];
        if(curKc == Kc)
        {
            bool check_contain = checkIfContain(collection, r, c);
            if(!check_contain)
            {
                collection.push_back(co);
                queues.push(co);
            }
        }
    }
}

bool match::checkBundary(int r, int c)
{
    if(r<0 || r>=ROW)
        return false;
    
    if(c<0 || c>=COL)
        return false;
    
    return true;
}

bool match::checkIfContain(const std::vector<coord>& colleciton, int r, int c)
{
    coord co;
    co.r = r;
    co.c = c;
    const std::vector<coord>::const_iterator it = std::find(colleciton.cbegin(), colleciton.cend(), co);
    if(it == colleciton.cend())
        return false;
    return true;
}

void match::boxDeadEffect(const std::vector<coord>& collections)
{
    std::vector<coord>::const_iterator it = collections.begin();
    for(; it != collections.end(); ++it)
    {
        coord co = *it;
        int r = co.r;
        int c = co.c;
        
        auto emitter = ParticleSystemQuad::create("Particles/SmallSun.plist");
        emitter->setStartColor(Color4F(1,0,0,1));
        emitter->setBlendAdditive(false);
        addChild(emitter);
        emitter->setPosition(_boxesPos[r][c]);
        emitter->setDuration(0.2f);
    }
}

void match::moveBoxes(const std::vector<coord>& collections)
{
    for(int i=0; i<collections.size(); i++)
    {
        coord co = collections[i];
        int r = co.r;
        int c = co.c;
        CCLOG("r=%d, c=%d\n",r,c);
        
        _rc[r][c] = kUnSigned;
        if(_rcSprites[r][c])
        {
            _rcSprites[r][c]->removeFromParentAndCleanup(true);
            _rcSprites[r][c]=nullptr;
        }
    }
    
    for(int c=0; c<COL; c++)
       moveRowBoxes(c);
}

void match::resetCanbeTouch()
{
    _canbTouch = true;
    _bShowTip = false;
    _updateTime = 0.0f;
    _updateTipTime = 0.0f;
    _updateGrayTime = 0.0f;
    _updateBarTime = 0.0f;
}

void match::moveOneBox(int c)
{
    //find the first unsigned
    int r=0;
    while (_rc[r][c] != kUnSigned && r<ROW)
        r=r+1;
    
    if(r >= ROW)
        return;
    
    int first = r;
    
    //find the first not unsigned
    while(_rc[r][c] == kUnSigned && r<ROW)
        r=r+1;
    
    if(r >= ROW)
        return;
    
    //move to destination
    Point destnation = _boxesPos[first][c];
    Sprite* sp = _rcSprites[r][c];
    auto action = moveAction(destnation);
    sp->runAction(action);
    
    //set _rc & _rcSprite
    _rc[first][c] = _rc[r][c];
    _rc[r][c] = kUnSigned;
    
    _rcSprites[first][c] = _rcSprites[r][c];
    _rcSprites[r][c] = nullptr;
}

void match::moveRowBoxes(int c)
{
    for(int r=0; r<ROW; r++)
        moveOneBox(c);
    
    int cnt = 0;
    for(int r=0; r<ROW; r++)
    {
        if(_rc[r][c] == kUnSigned)
            cnt += 1;
    }
    
    for(int i=0, r=ROW-cnt; r<ROW; r++, i++)
    {
        Point pt = _boxesPos[r][c];
    
        Color3B color3B;
        colorSpriteEnum randomEnum;
        randomColor(color3B,randomEnum);
        auto sprite = Sprite::create("Icon.png");
    
        sprite->setTag(r*ROW+c);
        sprite->setColor(color3B);
        _rcSprites[r][c] = sprite;
        _rc[r][c] = randomEnum;
    
        sprite->setPosition(Point(pt.x, pt.y + 20));
        auto action = moveAction(pt);
        sprite->runAction(action);
        _boxParentNode->addChild(sprite);
    }
}

cocos2d::ActionInterval* match::moveAction(Point pt)
{
    MoveTo* move = MoveTo::create(MOVEDURATION, pt);
    auto move_ease_inout1 = EaseBounceOut::create(move);
    return move_ease_inout1;
}

void match::randomColor(Color3B& color3B, colorSpriteEnum& randomEnum)
{
    int idc = CCRANDOM_0_1()*5+1;
    switch (idc) {
        case 1:
            color3B = Color3B::YELLOW;
            randomEnum = kA;
            break;
        case 2:
            color3B = Color3B::BLUE;
            randomEnum = kB;
            break;
        case 3:
            color3B = Color3B::GREEN;
            randomEnum = kC;
            break;
        case 4:
            color3B = Color3B::ORANGE;
            randomEnum = kD;
            break;
        case 5:
            color3B = Color3B::GRAY;
            randomEnum = kE;
            break;
        default:
            break;
    }
    return;
}

void match::randomShowMatchTip()
{
    if(_bShowTip)
        return;
    
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            std::vector<coord> collection;
            findSameColorsSprite(r, c, collection);
            if(collection.size() > 2){
                
                clearMatchTips();
                _bShowTip = true;
                
                for(int i=0; i<collection.size(); i++){
                    coord co = collection[i];
                    int r = co.r;
                    int c = co.c;
                    
                    Sprite* tip = Sprite::create("circle.png");
                    this->addChild(tip);
                    tip->setPosition(_boxesPos[r][c]);
                    _showTips.pushBack(tip);
                    
                    auto actionScaleTo = ScaleTo::create(1, 0.44f, 0.47f);
                    auto actionScaleToBack = ScaleTo::create(1, 1.0f, 1.0f);
                    auto sequene  = Sequence::create(actionScaleTo, actionScaleToBack, NULL);
                    auto repeat = RepeatForever::create(sequene);
                    tip->runAction(repeat);
                }
                return;
            }
        }
    }
}

void match::clearMatchTips()
{
    for(int i=0; i<_showTips.size(); i++)
    {
        Sprite* tip = _showTips.at(i);
        tip->removeFromParentAndCleanup(true);
    }
    _showTips.clear();
}

void match::update(float delta)
{
    _updateGrayTime += delta;
    if(_updateGrayTime >= 1.0f)
    {
        _updateGrayTime = 0.0f;
        clearGraySprites();
    }
    
    _updateTipTime += delta;
    if(_updateTipTime >= 5.0f)
    {
        _updateTipTime = 0.0f;
        randomShowMatchTip();
    }
    
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
            popupLayer();
            unscheduleUpdate();
            resetCanbeTouch();
        }
    }
}

int match::computeMatches()
{
    bool boxes[ROW][COL];
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            boxes[r][c] = false;
        }
    }
    
    std::vector<std::vector<coord>> cs;
    
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            if(!boxes[r][c])
            {
                std::vector<coord> collection;
                findSameColorsSprite(r,c,collection);
                
                if(collection.size() >= 3)
                    cs.push_back(collection);
                
                for(int i=0; i<collection.size(); i++)
                {
                    coord co = collection[i];
                    boxes[co.r][co.c] = true;
                }
            }
        }
    }
    return cs.size();
}

void match::setupEnergyProgress()
{
    auto s = Director::getInstance()->getWinSize();
    auto boxbk_size = getChildByTag(kBoxBk)->getContentSize();
    auto back = Sprite::create("sliderTrack.png");
    addChild(back,0,kEneryBar);
    back->setPosition(Point(s.width/2,
                            _boxbkPos.y + back->getContentSize().height/2 + boxbk_size.height+60));
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("sliderProgress.png");
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

void match::setupTimerProgress()
{
    auto s = Director::getInstance()->getWinSize();
    auto back = Sprite::create("sliderTrack.png");
    addChild(back,0,kTimerBar);
    back->setPosition(Point(s.width/2,
                            _boxbkPos.y - back->getContentSize().height/2 - 10));
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("sliderProgress.png");
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

void match::setupMonster()
{
    this->removeChildByTag(kMonsterHp);
    this->removeChildByTag(kMonster);
    
    auto s = Director::getInstance()->getWinSize();
    auto texture = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");
    
    // manually add frames to the frame cache
    auto frame0 = SpriteFrame::createWithTexture(texture, Rect(132*0, 132*0, 132, 132));
    auto frame1 = SpriteFrame::createWithTexture(texture, Rect(132*1, 132*0, 132, 132));
    auto frame2 = SpriteFrame::createWithTexture(texture, Rect(132*2, 132*0, 132, 132));
    auto frame3 = SpriteFrame::createWithTexture(texture, Rect(132*3, 132*0, 132, 132));
    auto frame4 = SpriteFrame::createWithTexture(texture, Rect(132*0, 132*1, 132, 132));
    auto frame5 = SpriteFrame::createWithTexture(texture, Rect(132*1, 132*1, 132, 132));
    
    //Animation using Sprite BatchNode
    auto sprite = Sprite::createWithSpriteFrame(frame0);
    addChild(sprite,0,kMonster);
    
    auto boxbk = (Sprite*)this->getChildByTag(kBoxBk);
    sprite->setPosition(Point(boxbk->getPosition().x + boxbk->getContentSize().width,
                              boxbk->getPosition().y + boxbk->getContentSize().height + sprite->getContentSize().height/2 + 20));
    
    Vector<SpriteFrame*> animFrames(6);
    animFrames.pushBack(frame0);
    animFrames.pushBack(frame1);
    animFrames.pushBack(frame2);
    animFrames.pushBack(frame3);
    animFrames.pushBack(frame4);
    animFrames.pushBack(frame5);
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    auto animate = Animate::create(animation);
    sprite->runAction(RepeatForever::create(animate));
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width/3);
    
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x01);
    body->setMass(100);
    body->setMoment(100);
    body->setDynamic(false);
    
    sprite->setPhysicsBody(body);
    _monster_Pos = Point(sprite->getPosition().x - sprite->getContentSize().width/4,
                         sprite->getPosition().y - sprite->getContentSize().height/2);
    
    //setup monster hp
    auto bkbar = Sprite::create("slidbar.png");
    bkbar->setColor(Color3B::GRAY);
    addChild(bkbar,0,kMonsterHp);
    bkbar->setPosition(Point(_monster_Pos.x - sprite->getContentSize().width/2 + bkbar->getContentSize().width/2, _monster_Pos.y-6));
    
    LoadingBar* monsterHpBar = LoadingBar::create();
    monsterHpBar->setTag(0);
    monsterHpBar->loadTexture("slidbar.png");
    monsterHpBar->setDirection(LoadingBarTypeLeft);
    monsterHpBar->setPercent(100);
    monsterHpBar->setPosition(Point(bkbar->getContentSize().width/2, bkbar->getContentSize().height/2));
    bkbar->addChild(monsterHpBar,0,0);
}

void match::attackMonster(const std::vector<coord>& coords)
{
    std::vector<coord>::const_iterator it = coords.begin();
    for(int i=0; it!= coords.end(); ++it, ++i)
    {
        coord co = *it;
        int r = co.r;
        int c = co.c;
        
        auto sprite = Sprite::create("circle.png");
        auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
        
        body->setCategoryBitmask(0x04);
        body->setCollisionBitmask(0x04);
        body->setGroup(10);
        body->setVelocity(Vect(100,100));
        body->setMass(100);
        
        sprite->setPhysicsBody(body);
        sprite->setPosition(_boxesPos[r][c]);
        
        auto delay = DelayTime::create(i*0.15f);
        auto moveto = MoveTo::create(0.5f, _monster_Pos);
        auto stop = CallFunc::create( std::bind(&match::stopBulleSpeed, this, sprite));
        auto xs = Sequence::create(DelayTime::create(0.3f), stop, NULL);
        auto spawn = Spawn::create(moveto,xs,NULL);
        auto fadeout = FadeOut::create(1.0f);
        auto monsterHp = CallFunc::create( std::bind(&match::computeAttack, this));
        auto removeSelf = RemoveSelf::create();
        auto seq = Sequence::create(delay,spawn,monsterHp,fadeout,removeSelf,NULL);
        sprite->runAction(seq);
        this->addChild(sprite);
    }
}

void match::computeAttack()
{
    auto bkbar = (Sprite*)getChildByTag(kMonsterHp);
    auto loadingBar = (LoadingBar*)bkbar->getChildByTag(0);
    int percent = loadingBar->getPercent();
    percent -= 5;
    
    if(percent <= 0){
        percent = 100;
        setupMonster();
    }
    else
        loadingBar->setPercent(percent);
    return;
}

void match::stopBulleSpeed(Sprite* bullet)
{
    bullet->getPhysicsBody()->setVelocity(Vect(0,0));
}

void match::createRabbit()
{
    auto sprite = Sprite::create("circle.png");
    sprite->setColor(Color3B::MAGENTA);
    _boxParentNode->addChild(sprite);
    
    int r = CCRANDOM_0_1()*(ROW-1)+0;
    int c = CCRANDOM_0_1()*(COL-1)+0;
    
    _rc[r][c] = kRabbit;
    _rcSprites[r][c]->removeFromParentAndCleanup(true);
    _rcSprites[r][c] = sprite;
    sprite->setPosition(_boxesPos[r][c]);
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
    //auto director = Director::getInstance();
    //director->getTouchDispatcher()->removeDelegate(this);
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
    if(_canbTouch == false)
    {
        CCLOG("_canbTouch is false");
        return;
    }
    _canbTouch = false;
    detectSprite(touch);
}

bool match::onContactBegin(EventCustom *event, const PhysicsContact& contact)
{
    auto b1 = (PhysicsBody*)contact.getShapeA()->getBody();
    auto b2 = (PhysicsBody*)contact.getShapeB()->getBody();
    
    if(b1->getCollisionBitmask() != b2->getCollisionBitmask())
    {
        //b1->getNode()->removeFromParentAndCleanup(true);
    }
    CCLOG("onContactBegin %d, %d", b1->getCollisionBitmask(), b2->getCollisionBitmask());
    return true;
}

void match::setupButton()
{
    auto s = Director::getInstance()->getWinSize();
    auto button1 = createButton("backtotopnormal.png", "backtotoppressed.png");
    addChild(button1);
    
    button1->setPosition(Point(s.width/2, s.height-100));
    button1->addTouchEventListener(this, toucheventselector(match::touchEvent1));
    
    Label* label1 = createLabel();
    button1->getVirtualRenderer()->addChild(label1);
    label1->setPosition(Point(button1->getContentSize().width/2, button1->getContentSize().height/2));
    label1->setString("freshBoxes");
}

Button* match::createButton(const char* normal, const char* pressed)
{
    Button* button = Button::create();
    button->setTouchEnabled(true);
    button->loadTextures(normal, pressed, "");
    return button;
}

Label* match::createLabel()
{
    auto s = Director::getInstance()->getWinSize();
    TTFConfig ttfConfig("fonts/arial.ttf", 30, GlyphCollection::DYNAMIC,nullptr,true);
    auto label = Label::createWithTTF(ttfConfig,"ReStart",TextHAlignment::CENTER,s.width);
    label->setColor( Color3B::WHITE );
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    return label;
}

void match::touchEvent1(Object *pSender, TouchEventType type)
{
    createBoxes();
}

void match::touchEvent2(Object *pSender, TouchEventType type)
{
    float duration = 0.5f;
    auto mainScene = mainEnter::createScene();
    auto scene = TransitionFade::create(duration, mainScene, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
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

void match::addEneryBar(float unit_percent)
{
    auto back = (Sprite*)this->getChildByTag(kEneryBar);
    auto loading = (LoadingBar*)back->getChildByTag(0);
    float  cur_percent = loading->getPercent();
    
    cur_percent += unit_percent;
    
    if(cur_percent >= 100)
    {
        petAttack();
        cur_percent -= 100;
    }
    
    loading->setPercent(cur_percent);
    auto label = (Label*)back->getChildByTag(1);
    char buf[10];
    sprintf(buf, "%d", (int)(cur_percent));
    label->setString(buf);
    CCLOG("cur_percent:%f\n", cur_percent);
}

void match::setupPets()
{
    this->removeChildByTag(kRabbitPet);
    auto s = Director::getInstance()->getWinSize();
    auto texture = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");
    // manually add frames to the frame cache
    auto frame0 = SpriteFrame::createWithTexture(texture, Rect(132*0, 132*0, 132, 132));
    auto frame1 = SpriteFrame::createWithTexture(texture, Rect(132*1, 132*0, 132, 132));
    auto frame2 = SpriteFrame::createWithTexture(texture, Rect(132*2, 132*0, 132, 132));
    auto frame3 = SpriteFrame::createWithTexture(texture, Rect(132*3, 132*0, 132, 132));
    auto frame4 = SpriteFrame::createWithTexture(texture, Rect(132*0, 132*1, 132, 132));
    auto frame5 = SpriteFrame::createWithTexture(texture, Rect(132*1, 132*1, 132, 132));
    
    //Animation using Sprite BatchNode
    auto sprite = Sprite::createWithSpriteFrame(frame0);
    addChild(sprite,0,kRabbitPet);
    
    auto boxbk = (Sprite*)this->getChildByTag(kBoxBk);
    sprite->setPosition(Point(boxbk->getPosition().x,
                              boxbk->getPosition().y + boxbk->getContentSize().height + sprite->getContentSize().height/2 + 20));
    
    Vector<SpriteFrame*> animFrames(6);
    animFrames.pushBack(frame0);
    animFrames.pushBack(frame1);
    animFrames.pushBack(frame2);
    animFrames.pushBack(frame3);
    animFrames.pushBack(frame4);
    animFrames.pushBack(frame5);
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    auto animate = Animate::create(animation);
    sprite->runAction(RepeatForever::create(animate));
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width/3);
    
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x01);
    body->setMass(100);
    body->setMoment(100);
    body->setDynamic(false);
    sprite->setPhysicsBody(body);
    sprite->setFlippedX(true);
    _pet_Pos = sprite->getPosition();
}

void match::petAttack()
{
    for(int i=0; i<4; i++)
    {
        auto sprite = Sprite::create("circle.png");
        auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
        
        body->setCategoryBitmask(0x04);
        body->setCollisionBitmask(0x04);
        body->setGroup(10);
        body->setVelocity(Vect(100,100));
        body->setMass(100);
        
        sprite->setPhysicsBody(body);
        sprite->setPosition(_pet_Pos);
        
        auto delay = DelayTime::create(i*0.15f);
        auto moveto = MoveTo::create(0.5f, _monster_Pos);
        auto stop = CallFunc::create( std::bind(&match::stopBulleSpeed, this, sprite));
        auto xs = Sequence::create(DelayTime::create(0.3f), stop, NULL);
        auto spawn = Spawn::create(moveto,xs,NULL);
        auto fadeout = FadeOut::create(1.0f);
        auto monsterHp = CallFunc::create(std::bind(&match::computeAttack, this));
        auto removeSelf = RemoveSelf::create();
        auto seq = Sequence::create(delay,spawn,monsterHp,fadeout,removeSelf, NULL);
        sprite->runAction(seq);
        this->addChild(sprite);
    }
}

void match::setupPauseButton()
{
    auto s = Director::getInstance()->getWinSize();
    auto pauseButtn = createButton("ui_pause_up.png", "ui_pause_down.png");
    addChild(pauseButtn);
    pauseButtn->setPosition(Point(s.width-pauseButtn->getContentSize().width/2, s.height-pauseButtn->getContentSize().height/2));
    pauseButtn->addTouchEventListener(this, toucheventselector(match::pauseEvent));
    return;
}

void match::pauseEvent(cocos2d::Object  *pSender, TouchEventType type)
{
    auto s = Director::getInstance()->getWinSize();
	RenderTexture *renderTexture = RenderTexture::create(s.width, s.height);
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();
    Director::getInstance()->pushScene( CCTransitionFade::create( 0.5f, PauseLayer::scene(renderTexture,true)));
}
