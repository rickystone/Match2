//
//  coreMatch.cpp
//  Match
//
//  Created by 程小二 on 14-2-13.
//
//

#include "coreMatch.h"
#include "Attack.h"

coreMatch::coreMatch()
: _batchnode(nullptr),
  _updateTime(0),
  _updateGrayTime(0),
  _updateTipTime(0),
  _updateBarTime(0),
  _updateCrazyTime(0),
  _canbTouch(true),
  _bShowTip(false),
  _continueAddTime(0),
  _continueTimes(0),
  _kRenderTextureCount(6),
  _currentRenderTextureIndex(0),
  _monster_Pos(-1, -1)

{}

coreMatch::~coreMatch() {}

coreMatch* coreMatch::create()
{
    coreMatch* pret = new coreMatch;
    pret->autorelease();
    pret->init();
    return pret;
}

bool coreMatch::init()
{
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            _rc[r][c] = kUnSigned;
            _boxesPos[r][c] = Point(-1,-1);
            _rcSprites[r][c] = nullptr;
        }
    }
    
    setupMotionBlur();
    setBkGround();
    createBoxes();
    scheduleUpdate();
    return true;
}

void coreMatch::onTouch(Touch* touch)
{
    if(_canbTouch == false)
    {
        return;
    }
    _canbTouch = false;
    touchOneBox(touch);
}

void coreMatch::setBkGround()
{
    auto s = Director::getInstance()->getWinSize();
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("matchBox/item.plist", "matchBox/item.png");
    _batchnode = SpriteBatchNode::create("matchBox/item.png");
    this->addChild(_batchnode,0,10);
    
    auto sprite = Sprite::createWithSpriteFrameName("s_fanqie.png");
    auto size = sprite->getContentSize();
    _batchnode->setPosition(Point(0,0));
}

void coreMatch::createItemBox(int r, int c)
{
    colorSpriteEnum randomEnum;
    std::string spriteFrameFileName = "";
    randomColor(randomEnum,spriteFrameFileName);
    auto sprite = Sprite::createWithSpriteFrameName(spriteFrameFileName.c_str());
    
    _rc[r][c] = randomEnum;
    _rcSprites[r][c] = sprite;
    
    sprite->setPosition(_boxesPos[r][c]);
    sprite->setTag(r*ROW+c);
    _batchnode->addChild(sprite);
    return ;
}

void coreMatch::createBoxes()
{
    auto sprite = Sprite::createWithSpriteFrameName("s_fanqie.png");
    auto size = sprite->getContentSize();
    _batchnode->removeAllChildrenWithCleanup(true);
    
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
    
    int space = 1;
    Point start = Point(0,0);
    for(int r=0; r<ROW; r++)
    {
        Point prevPt = Point(start.x + size.width/2+space, start.y + r*size.height + size.height/2 + 2);
        for(int c=0; c<COL; c++)
        {
            _boxesPos[r][c] = prevPt;
            prevPt = Point(prevPt.x + size.width+ space, prevPt.y);
        }
    }
    
    Vector<FiniteTimeAction*> functionVecs;
    auto delay = DelayTime::create(1.0f);
    functionVecs.pushBack(delay);
    
    std::vector<std::vector<coord>>::iterator it = rcs.begin();
    for(; it != rcs.end(); ++it)
    {
        std::vector<coord>::iterator xi = it->begin();
        for(; xi != it->end(); ++xi)
        {
            coord cr = *xi;
            int r = cr.r;
            int c = cr.c;
            
            auto call = CallFunc::create(std::bind(&coreMatch::createItemBox,this,r,c));
            auto delay = DelayTime::create(0.01f);
            functionVecs.pushBack(call);
            functionVecs.pushBack(delay);
        }
    }
    Sequence* seq = Sequence::create(functionVecs);
    this->runAction(seq);
}

void coreMatch::randomColor(colorSpriteEnum& randomEnum, std::string& spriteFrameFileName)
{
    int idc = CCRANDOM_0_1()*5+1;
    switch (idc) {
        case 1:
            randomEnum = kA;
            spriteFrameFileName = "s_fanqie_b.png";
            break;
            
        case 2:
            randomEnum = kB;
            spriteFrameFileName = "s_lanmei_b.png";
            break;
            
        case 3:
            randomEnum = kC;
            spriteFrameFileName = "s_qiezi_b.png";
            break;
        case 4:
            randomEnum = kD;
            spriteFrameFileName = "s_tudou_b.png";
            break;
            
        case 5:
            randomEnum = kE;
            spriteFrameFileName = "s_xigua_b.png";
            break;
            
        default:
            break;
    }
    return;
}

void coreMatch::setupGraySprite(int r, int c)
{
    Sprite* sprite = _rcSprites[r][c];
    if(sprite)
        sprite->setVisible(false);
    
    Point pt = _boxesPos[r][c];
    pt = _batchnode->convertToWorldSpace(pt);
    
    colorSpriteEnum  ce = _rc[r][c];
    std::string s_open = "", s_close = "";
    
    switch (ce) {
        case kA:
            s_open = "matchBox/s_fanqie.png";
            s_close = "matchBox/s_fanqie_b.png";
            break;
            
        case kB:
            s_open = "matchBox/s_lanmei.png";
            s_close = "matchBox/s_lanmei_b.png";
            break;
            
        case kC:
            s_open = "matchBox/s_qiezi.png";
            s_close = "matchBox/s_qiezi_b.png";
            break;
            
        case kD:
            s_open = "matchBox/s_tudou.png";
            s_close = "matchBox/s_tudou_b.png";
            break;
            
        case kE:
            s_open = "matchBox/s_xigua.png";
            s_close = "matchBox/s_xigua_b.png";
            break;
            
        default:
            break;
    }
    
    GreyScaleSprite *ss = GreyScaleSprite::createSprite(s_open.c_str());
    ss->setPosition(pt);
    this->addChild(ss);
    ss->setTag(r*ROW+c);
    _graysprites.pushBack(ss);
    
    //run animation
    Animation* animation = Animation::create();
    animation->addSpriteFrameWithFile(s_open);
    animation->addSpriteFrameWithFile(s_close);
    animation->addSpriteFrameWithFile(s_open);
    animation->addSpriteFrameWithFile(s_close);
    animation->addSpriteFrameWithFile(s_open);
    animation->addSpriteFrameWithFile(s_close);
    
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.8f/6.0);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    if(ss)
    {
        ss->stopAllActions();
        ss->runAction(RepeatForever::create(action));
    }
}

void coreMatch::clearGraySprites()
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

void coreMatch::touchOneBox(cocos2d::Touch *touch)
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
                        _continueTimes = 0;
                        _continueAddTime = 0;
                        resetCanbeTouch();
                        return;
                    }
                    else if(collections.size() >= 3)
                    {
                        //clearMatchTips();
                        _bShowTip = true;
                        _continueTimes += 1;
                        if(_continueTimes == 1)
                            _continueAddTime = 0;
                        
                        CCLOG(" time & cunt :%f, %d\n", _continueAddTime, _continueTimes);
                        if(_continueAddTime <= CRAZYTIME && _continueTimes >= CRAZYCOUNT && _updateCrazyTime <= 0)
                        {
                            CCLOG("enter crazy status\n");
                            enterCrazyStatus();
                        }
                        
                        /*
                         1: box dead effect
                         2: attack monster
                         3: movebox
                        */
                        
                        //std::sort(std::begin(collections), std::end(collections), coordCompareLess );
                        auto boxdead = CallFunc::create( std::bind(&coreMatch::boxDeadEffect, this, collections));
                        auto movebox = CallFunc::create( std::bind(&coreMatch::moveBoxes, this));
                        auto attackMonster = CallFunc::create( std::bind(&coreMatch::attackMonster, this, collections));
                        auto reset = CallFunc::create( std::bind(&coreMatch::resetCanbeTouch,this));
                        auto sequence = Sequence::create(boxdead,
                                                         DelayTime::create(0.2f),
                                                         attackMonster,
                                                         movebox,
                                                         DelayTime::create(MOVEDURATION),
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

void coreMatch::findSameColorsSprite(int r, int c, std::vector<coord>& collection)
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

void coreMatch::processRC(std::queue<coord>& queues, std::vector<coord>& collection, colorSpriteEnum curKc, int r, int c)
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

bool coreMatch::checkBundary(int r, int c)
{
    if(r<0 || r>=ROW)
        return false;
    
    if(c<0 || c>=COL)
        return false;
    
    return true;
}

bool coreMatch::checkIfContain(const std::vector<coord>& colleciton, int r, int c)
{
    coord co;
    co.r = r;
    co.c = c;
    const std::vector<coord>::const_iterator it = std::find(colleciton.cbegin(), colleciton.cend(), co);
    if(it == colleciton.cend())
        return false;
    return true;
}

void coreMatch::boxDeadEffect(const std::vector<coord>& collections)
{
    for(int i=0; i<collections.size(); i++)
    {
        coord co = collections[i];
        int r = co.r;
        int c = co.c;
        
        _rc[r][c] = kUnSigned;
        if(_rcSprites[r][c])
        {
            _rcSprites[r][c]->removeFromParentAndCleanup(true);
            _rcSprites[r][c]=nullptr;
        }
    }
    
    std::vector<coord>::const_iterator it = collections.begin();
    for(; it != collections.end(); ++it)
    {
        coord co = *it;
        int r = co.r;
        int c = co.c;
        
        auto emitter = ParticleSystemQuad::create("Particles/boomb.plist");
        emitter->setStartColor(Color4F(1,0,0,1));
        emitter->setBlendAdditive(false);
        emitter->setScale(0.5f);
        addChild(emitter);
        
        Point pt = _batchnode->convertToWorldSpace(_boxesPos[r][c]);
        emitter->setPosition(pt);
        emitter->setDuration(0.2f);
        
        //play bomb sound
    }
}


void coreMatch::moveBoxes()
{
    for(int c=0; c<COL; c++)
        moveRowBoxes(c);
}

void coreMatch::moveOneBox(Vector<Sprite*>& runSprites, Vector<FiniteTimeAction*>& runActions, int c)
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
    auto action = moveAction(MOVEDURATION,destnation);
    
    runSprites.pushBack(sp);
    runActions.pushBack(action);
    
    //set _rc & _rcSprite
    _rc[first][c] = _rc[r][c];
    _rc[r][c] = kUnSigned;
    
    _rcSprites[first][c] = _rcSprites[r][c];
    _rcSprites[r][c] = nullptr;
}


void coreMatch::moveRowBoxes(int c)
{
    Vector<Sprite*> runSprites;
    Vector<FiniteTimeAction*> runActions;
    Vector<FiniteTimeAction*> shitVec;

    float stepDuration = 1.0f*MOVEDURATION/4;

    for(int r=0; r<ROW; r++)
        moveOneBox(runSprites, runActions, c);
    
    boxCollectionSeqeunceMove(shitVec, runSprites,runActions);
    runActions.clear();
    runSprites.clear();
    
    //idle for one step duration
    shitVec.pushBack(DelayTime::create(stepDuration));
    
    
    //born new box and make it move down
    int cnt = 0;
    for(int r=0; r<ROW; r++)
    {
        if(_rc[r][c] == kUnSigned)
            cnt += 1;
    }
    for(int i=0, r=ROW-cnt; r<ROW; r++, i++)
    {
        fucknewBox(runSprites, runActions, r, c);
    }

    //make new born box move action
    boxCollectionSeqeunceMove(shitVec, runSprites,runActions);
    runActions.clear();
    runSprites.clear();
    
    
    auto seq = Sequence::create(shitVec);
    this->runAction(seq);
}

void coreMatch::fucknewBox(Vector<Sprite*>& runSprites, Vector<FiniteTimeAction*>& runActions, int r, int c)
{
    Point pt = _boxesPos[r][c];
    colorSpriteEnum randomEnum;
    std::string spriteFrameFileName = "";
    randomColor(randomEnum,spriteFrameFileName);
    
    auto sprite = Sprite::createWithSpriteFrameName(spriteFrameFileName.c_str());
    sprite->setTag(r*ROW+c);
    _rcSprites[r][c] = sprite;
    _rc[r][c] = randomEnum;
    
    sprite->setPosition(Point(pt.x, pt.y+600));
    auto action = moveAction(MOVEDURATION, pt);
    
    runSprites.pushBack(sprite);
    runActions.pushBack(action);
    
    _batchnode->addChild(sprite);
}

cocos2d::ActionInterval* coreMatch::moveAction(float duration, Point pt)
{
    MoveTo* move = MoveTo::create(duration, pt);
    return move;
    
    auto move_ease_inout = EaseBounceOut::create(move);
    return move_ease_inout;
}

void coreMatch::boxMove(Sprite* box, FiniteTimeAction* moveAction)
{
    box->runAction(moveAction);
}


void coreMatch::boxCollectionSeqeunceMove(Vector<FiniteTimeAction*>& shitVec,
                                          const Vector<Sprite*>& sprites,
                                          const Vector<FiniteTimeAction*>& actions)
{
    float stepDuration = 1.0f*MOVEDURATION/4;
    for(int i=0; i<sprites.size(); i++)
    {
        auto sp = sprites.at(i);
        auto move = actions.at(i);
        
        //i do not know why must have add retain
        move->retain();
        
        auto del = DelayTime::create(stepDuration);
        auto func = CallFunc::create(std::bind(&coreMatch::boxMove,this, sp, move));
        shitVec.pushBack(del);
        shitVec.pushBack(func);
    }
    return;
}

void coreMatch::clearMatchTips()
{
    for(int i=0; i<_showTips.size(); i++)
    {
        Sprite* tip = _showTips.at(i);
        tip->removeFromParentAndCleanup(true);
    }
    _showTips.clear();
}

void coreMatch::attackMonster(const std::vector<coord>& coords)
{
    int index = CCRANDOM_0_1()*(coords.size()-1);
    coord co = coords[index];
    int r = co.r;
    int c = co.c;
    Attack*  att = Attack::create();
    addChild(att);
    Point pt = _batchnode->convertToWorldSpace(_boxesPos[r][c]);
    att->shootBullet(r, c, _monster_Pos, pt);
}

void coreMatch::randomShowMatchTip()
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
                   
                    //makeBoxSimle(r, c);
                    //createShowTipParticl(r,c);
                    
                    Sprite* tip = Sprite::create("circle.png");
                    this->addChild(tip);
                    Point pt = _batchnode->convertToWorldSpace(_boxesPos[r][c]);
                    tip->setPosition(pt);
                    _showTips.pushBack(tip);
                    
                    auto actionScaleTo = ScaleTo::create(1, 0.44f, 0.44f);
                    auto actionScaleToBack = ScaleTo::create(1, 1.5f, 1.5f);
                    
                    auto fadeout = FadeOut::create(1.0f);
                    auto fadeout_Back = fadeout->reverse();

                    auto sequene1  = Sequence::create(actionScaleTo, actionScaleToBack, NULL);
                    auto sequene2  = Sequence::create(fadeout, fadeout_Back, NULL);

                    auto repeat1 = RepeatForever::create(sequene1);
                    auto repeat2= RepeatForever::create(sequene2);

                    tip->runAction(repeat1);
                    tip->runAction(repeat2);

                }
                return;
            }
        }
    }
}

int coreMatch::computeMatchBoxes()
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

void coreMatch::makeBoxRun()
{
    //one time
    int r = CCRANDOM_0_1()*(ROW-1);
    int c = CCRANDOM_0_1()*(COL-1);
    bool ret = findOneBoxAndMakeItRun(r,c);
    while (!ret)
    {
        r = CCRANDOM_0_1()*(ROW-1);
        c = CCRANDOM_0_1()*(COL-1);
        ret = findOneBoxAndMakeItRun(r,c);
    }
    return;
}

bool coreMatch::findOneBoxAndMakeItRun(int r, int c)
{
    bool ret = false;
    std::vector<coord> collection;
    findSameColorsSprite(r, c, collection);
    if(collection.size() >= 2)
    {
        std::vector<coord>::iterator it = collection.begin();
        for(; it != collection.end(); ++it)
        {
            coord cd = *it;
            colorSpriteEnum  cs = _rc[cd.r][cd.c];
            
            //left
            bool bleft = recreateOneBox(cs, cd.r, cd.c-1);
            if(bleft)
                return true;
            
            //right
            bool bright = recreateOneBox(cs, cd.r, cd.c+1);
            if(bright)
                return true;
            
            //top
            bool btop = recreateOneBox(cs, cd.r+1, cd.c);
            if(btop)
                return true;
            
            //bottom
            bool bbottom = recreateOneBox(cs, cd.r-1, cd.c);
            if(bbottom)
                return true;
        }
    }
    return ret;
}

const char* coreMatch::getspriteFrameFileName(colorSpriteEnum ce)
{
    switch (ce) {
        case kA:
            return "s_fanqie_b.png";
            break;
        case kB:
            return "s_lanmei_b.png";
            break;
        case kC:
            return "s_qiezi_b.png";
            break;
        case kD:
            return "s_tudou_b.png";
            break;
        case kE:
            return "s_xigua_b.png";
            break;
        default:
            break;
    }
    return "";
}

bool coreMatch::recreateOneBox(colorSpriteEnum cs, int r, int c)
{
    if(r>=0 && r<=ROW-1 && c>=0 && c<=COL-1)
    {
        if(_rc[r][c] != cs)
        {
            _rc[r][c] = cs;
            _rcSprites[r][c]->removeFromParentAndCleanup(true);
            _rcSprites[r][c] = nullptr;
            const char* spriteFileFrameName = getspriteFrameFileName(cs);
            auto sprite = Sprite::createWithSpriteFrameName(spriteFileFrameName);
            _batchnode->addChild(sprite);
            sprite->setPosition(_boxesPos[r][c]);
            _rcSprites[r][c] = sprite;
            return true;
        }
    }
    return false;
}

void coreMatch::resetCanbeTouch()
{
    _canbTouch = true;
    _bShowTip = false;
    _updateTime = 0.0f;
    _updateTipTime = 0.0f;
    _updateGrayTime = 0.0f;
    _updateBarTime = 0.0f;
    clearMatchTips();

    int cnt = computeMatchBoxes();
    if(cnt <= 0)
    {
        makeBoxRun();
    }
}

void coreMatch::makeBoxSimle(int r, int c)
{
    auto sprite = _rcSprites[r][c];
    auto ce = _rc[r][c];
    std::string fileFrameName_open = "";
    std::string fileFrameName_close = "";
    
    switch (ce) {
        case kA:
            fileFrameName_open = "s_fanqie.png";
            fileFrameName_close = "s_fanqie_b.png";
            break;
            
        case kB:
            fileFrameName_open = "s_lanmei.png";
            fileFrameName_close = "s_lanmei_b.png";
            break;
            
        case kC:
            fileFrameName_open = "s_qiezi.png";
            fileFrameName_close = "s_qiezi_b.png";
            break;
            
        case kD:
            fileFrameName_open = "s_tudou.png";
            fileFrameName_close = "s_tudou_b.png";
            break;
            
        case kE:
            fileFrameName_open = "s_xigua.png";
            fileFrameName_close = "s_xigua_b.png";
            break;
            
        default:
            break;
    }
    
    Animation* animation = Animation::create();
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileFrameName_open));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileFrameName_close));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileFrameName_open));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileFrameName_close));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileFrameName_open));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileFrameName_close));
    
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.8f/ 6.0f);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    if(sprite)
    {
        sprite->stopAllActions();
        sprite->runAction(RepeatForever::create(action));
    }
}

void coreMatch::enterCrazyStatus()
{
    Animation* animation = Animation::create();
    for( int i=0; i<=4; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "effect/zt2_%05d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.6f / 24.0f);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    
    auto sprite = Sprite::create("effect/zt2_00000.png");
    sprite->runAction(RepeatForever::create(action));
    addChild(sprite,0,kCrazyEffect);
    
    auto s =  Director::getInstance()->getWinSize();
    sprite->setPosition(Point(sprite->getContentSize().width/2,
                              sprite->getContentSize().height/2 + _batchnode->getPosition().y));
    _updateCrazyTime =  CRAZTBURNTIME;
}

void coreMatch::quitCrazyStatus()
{
    _updateCrazyTime = 0;
    _continueAddTime = 0;
    _continueTimes = 0;
    this->removeChildByTag(kCrazyEffect);
}

void coreMatch::createShowTipParticl(int r, int c)
{
}

void coreMatch::setupMotionBlur()
{
    auto s = Director::getInstance()->getWinSize();
    _renderTextures.reserve(_kRenderTextureCount);
    
    for(int i=0; i<_kRenderTextureCount; i++)
    {
        RenderTexture *rtx = RenderTexture::create((int)s.width, (int)s.height);
        rtx->setPosition(Point(s.width/2,s.height/2));
        
        Sprite* renderSprite = Sprite::createWithTexture(rtx->getSprite()->getTexture());
        renderSprite->setPosition(rtx->getPosition());
        
        this->addChild(renderSprite,100+i);
        rtx->setUserData(renderSprite);
        
        _renderTextures.pushBack(rtx);
    }
}


void coreMatch::selectNextRenderTexture()
{
    _currentRenderTextureIndex++;
    if (_currentRenderTextureIndex >= _kRenderTextureCount)
    {
           _currentRenderTextureIndex = 0;
    }
}

void coreMatch::update(float delta)
{
    //update gray sprite, if show it, then for a while, clear this guys
    _updateGrayTime += delta;
    if(_updateGrayTime >= 1.0f)
    {
        _updateGrayTime = 0.0f;
        clearGraySprites();
    }
    
    //wait for a while, show some match tip guys
    _updateTipTime += delta;
    if(_updateTipTime >= 5.0f)
    {
        _updateTipTime = 0.0f;
        randomShowMatchTip();
    }
    
    _continueAddTime += delta;
    if(_continueAddTime >= CRAZYTIME)
    {
        _continueTimes = 0;
        _continueAddTime = 0;
    }
    
    if(_updateCrazyTime >0)
    {
        _updateCrazyTime -= delta;
        if(_updateCrazyTime <= 0)
        {
            quitCrazyStatus();
        }
    }
}

void coreMatch::visit()
{
    RenderTexture* rtx = _renderTextures.at(_currentRenderTextureIndex);
    rtx->beginWithClear(0, 0, 0, 0);
    for( const auto &child: _children){
        if(child->getTag() == 10)
            child->visit();
    }
    rtx->end();
    
    // reorder the render textures so that the
    // most recently rendered texture is drawn last
    this->selectNextRenderTexture();
    int index = _currentRenderTextureIndex;
    for (int i = 0; i < _kRenderTextureCount; i++){
        
            RenderTexture* rtx = _renderTextures.at(index);
            Sprite* renderSprite = (Sprite*)rtx->getUserData();
            renderSprite->setOpacity((255.0f / _kRenderTextureCount) * (i + 1));
            renderSprite->setScaleY(-1);
            this->reorderChild(renderSprite, 100+i);
            this->selectNextRenderTexture();
        
            index++;
            if (index >= _kRenderTextureCount) {
                    index = 0;
            }
    }
    
    for( const auto &child: _children){
        if(child->getTag() != 10)
            child->visit();
    }
}

