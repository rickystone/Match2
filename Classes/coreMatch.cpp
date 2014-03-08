//
//  coreMatch.cpp
//  Match
//
//  Created by 程小二 on 14-2-13.
//
//

#include "coreMatch.h"
#include "Attack.h"
#include "Prop.h"
#include "matchAlgorithm.h"


bool  coordCompare(const coord& n1, const coord& n2)
{
    if(n1.r == n2.r)
    {
        if(n1.c < n2.c)
            return true;
        else
            return false;
    }
    
    if(n1.c == n2.c)
    {
        if(n1.r < n2.r)
            return true;
        else
            return false;
    }
    
    if(n1.r < n2.r)
        return true;
    
    if(n1.c < n2.c)
        return true;
    
    return true;
}


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
  _propcount(0),
  _updatePropTime(0),
  _bProduceProp(false),
  _propSequence(0),
  _monster_Pos(-1, -1)
{}

coreMatch::~coreMatch()
{
}

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
    loadPlist();
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

//load box cache plist, use batchnode to add box
void coreMatch::loadPlist()
{
    auto s = Director::getInstance()->getWinSize();
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("matchBox/item.plist", "matchBox/item.png");
    _batchnode = SpriteBatchNode::create("matchBox/item.png");
    this->addChild(_batchnode,0,10);
    
    auto sprite = Sprite::createWithSpriteFrameName("s_fanqie.png");
    auto size = sprite->getContentSize();
    _batchnode->setPosition(Point(s.width/2 - size.width*ROW/2,size.height*2));
}

//create boxes when enter game, all box be added into batchonde,
//all boxed can be random produced
void coreMatch::createBoxes()
{
    auto sprite = Sprite::createWithSpriteFrameName("s_fanqie.png");
    auto size = sprite->getContentSize();
    _batchnode->removeAllChildrenWithCleanup(true);
    
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
    
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            colorSpriteEnum randomEnum;
            std::string spriteFrameFileName = "";
            matchAlgorithm::randomBox(randomEnum,spriteFrameFileName);
            createItemBox(r,c,randomEnum);
        }
    }
}

void coreMatch::createItemBox(int r, int c, colorSpriteEnum ce)
{
    const char* spriteFileName = matchAlgorithm::boxFileName(ce);
    auto sprite = Sprite::createWithSpriteFrameName(spriteFileName);
    _rc[r][c] = ce;
    
    if(_rcSprites[r][c])
    {
        _rcSprites[r][c]->removeFromParentAndCleanup(true);
        _rcSprites[r][c] = nullptr;
    }
    
    _rcSprites[r][c] = sprite;
    sprite->setPosition(_boxesPos[r][c]);
    sprite->setTag(r*ROW+c);
    _batchnode->addChild(sprite);
    return;
}


//make one guy to be grey
void coreMatch::setupGraySprite(int r, int c)
{
    Sprite* sprite = _rcSprites[r][c];
    if(sprite)
        sprite->setVisible(false);
    
    Point pt = _boxesPos[r][c];
    pt = _batchnode->convertToWorldSpace(pt);
    GreyScaleSprite *ss = matchAlgorithm::makeBoxBecomeGray(_rc[r][c]);
    ss->setScale(0.5f);
    ss->setPosition(pt);
    this->addChild(ss);
    ss->setTag(r*ROW+c);
    _graysprites.pushBack(ss);
}

//
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
                colorSpriteEnum rc = _rc[r][c];
                if(contain)
                {
                    clearGraySprites();
                    switch (rc) {
                            
                        //自动胶囊
                        case kPropAutoClear:
                        {
                            auto flash = CallFunc::create( std::bind(&coreMatch::flashLabelTTF, this, "自动胶囊", 30));
                            auto play = CallFunc::create( std::bind(&coreMatch::playPropAutoClear, this, r, c));
                            auto seq = Sequence::create(flash, DelayTime::create(1.0f),DelayTime::create(0.3), play, nullptr);
                            this->runAction(seq);
                        }
                            break;
                            
                        //炸弹胶囊
                        case kPropBoomb:
                        {
                            auto flash = CallFunc::create( std::bind(&coreMatch::flashLabelTTF, this, "炸弹胶囊", 30));
                            auto play = CallFunc::create( std::bind(&coreMatch::playPropBoomb, this, r, c));
                            auto seq = Sequence::create(flash, DelayTime::create(1.0f), play, nullptr);
                            this->runAction(seq);
                        }
                            break;
                        
                        //同色胶囊
                        case kPropSameColorBoomb:
                        {
                            auto flash = CallFunc::create( std::bind(&coreMatch::flashLabelTTF, this, "同色胶囊", 30));
                            auto play = CallFunc::create( std::bind(&coreMatch::playPropSameColorBoomb, this, r, c));
                            auto seq = Sequence::create(flash, DelayTime::create(1.0f),play, nullptr);
                            this->runAction(seq);
                        }
                            break;
                            
                        //十字炸弹
                        case kPropCorssBoomb:
                        {
                            auto flash = CallFunc::create( std::bind(&coreMatch::flashLabelTTF, this, "十字胶囊", 30));
                            auto play = CallFunc::create( std::bind(&coreMatch::playPropCrossBoomb, this, r, c));
                            auto seq = Sequence::create(flash, DelayTime::create(1.0f),play, nullptr);
                            this->runAction(seq);
                        }
                            break;
                            
                        //随机炸弹
                        case kPropRandomBoom:
                        {
                            auto flash = CallFunc::create( std::bind(&coreMatch::flashLabelTTF, this, "随机胶囊", 30));
                            auto play = CallFunc::create( std::bind(&coreMatch::playPropRandomBoomb, this, r, c));
                            auto seq = Sequence::create(flash,DelayTime::create(1.0f), play, nullptr);
                            this->runAction(seq);
                        }
                            break;
                            
                        //5色刷新
                        case kPropFivePlaces:
                        {
                            auto flash = CallFunc::create( std::bind(&coreMatch::flashLabelTTF, this, "5色胶囊", 30));
                            auto play = CallFunc::create( std::bind(&coreMatch::playPropFiveColorBoomb, this, r, c));
                            auto seq = Sequence::create(flash, DelayTime::create(1.0f),play, nullptr);
                            this->runAction(seq);
                        }
                            break;
                            
                        case kA:
                        case kB:
                        case kC:
                        case kD:
                        case kE:
                            this->playNormalBox(r,c);
                            break;
                        default:
                            break;
                    }
                    return;
                }
            }
        }
    }
    resetCanbeTouch();
}

void coreMatch::excuteDeadAndBornBoxes(std::vector<coord>& collections)
{
    int index = CCRANDOM_0_1()*(collections.size()-1);
    coord co = collections[index];

    std::sort(std::begin(collections), std::end(collections), coordCompare );
    auto movebox = CallFunc::create( std::bind(&coreMatch::moveBoxes, this));
    auto attackMonster = CallFunc::create( std::bind(&coreMatch::attackMonster, this, co.r, co.c));
    auto reset = CallFunc::create( std::bind(&coreMatch::resetCanbeTouch,this));
    
    Vector<FiniteTimeAction*> actions;
    boxSequenceDead(collections, actions);
    
    
    actions.pushBack(attackMonster);
    actions.pushBack(DelayTime::create(0.15f));
    actions.pushBack(movebox);
    actions.pushBack(DelayTime::create(MOVEDURATION));
    actions.pushBack(reset);
    
    auto seq = Sequence::create(actions);
    this->runAction(seq);
    return;
}

void coreMatch::boxSequenceDead(const std::vector<coord>& vecs, Vector<FiniteTimeAction*>& actions)
{
    std::vector<coord>::const_iterator it = vecs.begin();
    for(int i=0; it != vecs.end(); ++it, ++i)
    {
        coord cd = *it;
        int r = cd.r;
        int c = cd.c;
        
        auto delay = DelayTime::create(0.02);
        auto bind = CallFunc::create( std::bind(&coreMatch::boxDie, this, r,c));
        actions.pushBack(delay);
        actions.pushBack(bind);
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
    matchAlgorithm::randomBox(randomEnum,spriteFrameFileName);
    
    if(_bProduceProp)
    {
        colorSpriteEnum xx[] = {
            
            kPropAutoClear,       //自动胶囊
            kPropBoomb,           //炸弹胶囊
            kPropSameColorBoomb,  //同色胶囊
            
            kPropCorssBoomb,      //十字炸弹
            kPropRandomBoom,      //随机炸弹
            kPropFivePlaces,      //5色刷新
        };
        
        std::string filenames[] = {
            
            "d_sanxiao_zhadan.png",
            "d_zhadan.png",
            "d_tongse_zhadan.png",
            
            "d_shizi_zhadan.png",
            "d_20xiao_zhadan.png",
            "d_huanse.png",
        };
        
        int size = sizeof xx / sizeof(xx[0]);
        //int index = CCRANDOM_0_1()* (sizeof xx / sizeof(xx[0])-1);
        randomEnum = xx[_propSequence];
        spriteFrameFileName = filenames[_propSequence];
        
        _propcount = _propcount + 1;
        _propSequence = _propSequence + 1;
        if(_propSequence >= size)
            _propSequence = 0;

        _bProduceProp = false;
        _updatePropTime = 0;
        
        auto sprite = Sprite::createWithSpriteFrameName(spriteFrameFileName.c_str());
        sprite->setTag(r*ROW+c);
        _rcSprites[r][c] = sprite;
        _rc[r][c] = randomEnum;
        
        sprite->setPosition(Point(pt.x, pt.y+100));
        auto action = moveAction(MOVEDURATION, pt);
        
        runSprites.pushBack(sprite);
        runActions.pushBack(action);
        _batchnode->addChild(sprite);
        sprite->setVisible(false);
    }
    else
    {
        auto sprite = Sprite::createWithSpriteFrameName(spriteFrameFileName.c_str());
        sprite->setTag(r*ROW+c);
        _rcSprites[r][c] = sprite;
        _rc[r][c] = randomEnum;
        
        sprite->setPosition(Point(pt.x, pt.y+100));
        auto action = moveAction(MOVEDURATION, pt);
        
        runSprites.pushBack(sprite);
        runActions.pushBack(action);
        _batchnode->addChild(sprite);
        sprite->setVisible(false);
    }
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
    box->setVisible(true);
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
        sp->retain();
        
        auto del = DelayTime::create(stepDuration);
        auto func = CallFunc::create(std::bind(&coreMatch::boxMove,this, sp, move));
        shitVec.pushBack(del);
        shitVec.pushBack(func);
    }
    return;
}

void coreMatch::boxDie(int r, int c)
{
    _rc[r][c] = kUnSigned;
    if(_rcSprites[r][c])
    {
        _rcSprites[r][c]->removeFromParentAndCleanup(true);
        _rcSprites[r][c]=nullptr;
    }
    
    Point pt = _batchnode->convertToWorldSpace(_boxesPos[r][c]);
    auto emitter = ParticleSystemQuad::create("Particles/grapes_splurt.plist");
    addChild(emitter);
    emitter->setPosition(pt);
    emitter->setScale(0.5f);
    //emitter->setDuration(0.01);
    
    auto  seq = Sequence::create(DelayTime::create(0.5), RemoveSelf::create(), NULL);
    emitter->runAction(seq);
    //play bomb sound*/
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

void coreMatch::attackMonster(int r, int c)
{
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
            matchAlgorithm::findSameColorsSprite(_rc, r, c, collection);
            if(collection.size() > 2){
                
                clearMatchTips();
                _bShowTip = true;
                
                for(int i=0; i<collection.size(); i++){
                    coord co = collection[i];
                    int r = co.r;
                    int c = co.c;
                    
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

void coreMatch::resetCanbeTouch()
{
    _canbTouch = true;
    _bShowTip = false;
    _updateTime = 0.0f;
    _updateTipTime = 0.0f;
    _updateGrayTime = 0.0f;
    _updateBarTime = 0.0f;
    clearMatchTips();
    
    int cnt = matchAlgorithm::computeMatchBoxes(_rc);
    if(cnt <= 0)
    {
        matchAlgorithm::makeBoxRun(_rc, _boxesPos, _rcSprites, _batchnode);
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
    
    //update prop
    _updatePropTime += delta;
    if(_updatePropTime >= 5)
    {
        _updatePropTime = 0;
        _bProduceProp = true;
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
    
    //reorder the render textures so that the
    //most recently rendered texture is drawn last
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

void coreMatch::flashLabelTTF(const char *name, int fontsize)
{
    auto size = Director::getInstance()->getWinSize();
    // Adding "啊" letter at the end of string to make VS2012 happy, otherwise VS will generate errors
    // like "Error 3 error C2146: syntax error : missing ')' before identifier 'label'";
    TTFConfig ttfConfig("fonts/wt021.ttf",fontsize,GlyphCollection::DYNAMIC, name);
    auto label = Label::createWithTTF(ttfConfig, name, TextHAlignment::CENTER, size.width);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setPosition(Point(size.width / 2, size.height /2));
    label->setLabelEffect(LabelEffect::GLOW,Color3B::YELLOW);
    this->addChild(label);
    
    auto action = Sequence::create(
                                   ScaleTo::create(0.5f,4.0f,4.0f),
                                   ScaleTo::create(0.5f,1.0f,1.0f),
                                   nullptr);
    label->runAction(Sequence::create(action,RemoveSelf::create(),nullptr));
}

void coreMatch::playPropAutoClear(int r, int c)
{
    std::vector<std::vector<coord>> cs;
    Prop::propAutoBoomb(_rc, cs);
    std::vector<std::vector<coord>>::iterator it =cs.begin();
    for(; it != cs.end(); ++it)
    {
        excuteDeadAndBornBoxes(*it);
    }
    
    boxDie(r, c);
    _propcount -= 1;
}

void coreMatch::playPropBoomb(int r, int c)
{
    std::vector<coord> vecs;
    Prop::propBoomb(_rc,vecs,r,c);
    excuteDeadAndBornBoxes(vecs);
    boxDie(r, c);
    _propcount -= 1;
}

void coreMatch::playPropSameColorBoomb(int r, int c)
{
    std::vector<coord> vecs;
    Prop::propSameColorBoomb(_rc, vecs);
    excuteDeadAndBornBoxes(vecs);
    boxDie(r, c);
    _propcount -= 1;
}

void coreMatch::playPropCrossBoomb(int r, int c)
{
    std::vector<coord> rowVecs;
    std::vector<coord> colVecs;
    Prop::propCrossBooomb(_rc,r,c,rowVecs,colVecs);
    
    std::sort(std::begin(rowVecs), std::end(rowVecs), coordCompare);
    std::sort(std::begin(colVecs), std::end(colVecs), coordCompare);
    
    Vector<FiniteTimeAction*> actions;
    boxSequenceDead(rowVecs, actions);
    boxSequenceDead(colVecs, actions);
    
    auto movebox = CallFunc::create( std::bind(&coreMatch::moveBoxes, this));
    auto attackMonster = CallFunc::create( std::bind(&coreMatch::attackMonster, this, r,c));
    auto reset = CallFunc::create( std::bind(&coreMatch::resetCanbeTouch,this));
    
    actions.pushBack(attackMonster);
    actions.pushBack(DelayTime::create(0.15f));
    actions.pushBack(movebox);
    actions.pushBack(DelayTime::create(MOVEDURATION));
    actions.pushBack(reset);
    
    auto seq = Sequence::create(actions);
    this->runAction(seq);
    
    boxDie(r,c);
    _propcount -= 1;
}

void coreMatch::playPropRandomBoomb(int r, int c)
{
    std::vector<coord> vecs;
    Prop::propRandomBoomNBoxes(_rc, vecs);
    excuteDeadAndBornBoxes(vecs);
    boxDie(r,c);
    _propcount -= 1;
    return;

}

void coreMatch::playPropFiveColorBoomb(int r, int c)
{
    Prop::propFiveColorSpace(_rc);
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            auto ce = _rc[r][c];
            createItemBox(r, c, ce);
        }
    }
    
    clearGraySprites();
    clearMatchTips();
    
    _propcount -= 1;
    resetCanbeTouch();
}

void coreMatch::playNormalBox(int r, int c)
{
    std::vector<coord> collections;
    matchAlgorithm::findSameColorsSprite(_rc,r, c, collections);
    
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
        excuteDeadAndBornBoxes(collections);
        return;
    }
}





