//
//  matchAlgorithm.cpp
//  Match
//
//  Created by 程小二 on 14-2-25.
//
//

#include "matchAlgorithm.h"
#include "cocos2d.h"
#include "ShaderSprite.h"

USING_NS_CC;

void matchAlgorithm::findSameColorsSprite(const colorSpriteEnum _rc[ROW][COL], int r, int c, std::vector<coord>& collection)
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
        
        processRC(_rc, queues, collection, curKc, r-1, c);
        processRC(_rc, queues, collection, curKc, r+1, c);
        processRC(_rc, queues, collection, curKc, r, c+1);
        processRC(_rc, queues, collection, curKc, r, c-1);
    }
}

void matchAlgorithm::processRC(const colorSpriteEnum _rc[ROW][COL], std::queue<coord>& queues, std::vector<coord>& collection, colorSpriteEnum curKc, int r, int c)
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

bool matchAlgorithm::checkBundary(int r, int c)
{
    if(r<0 || r>=ROW)
        return false;
    
    if(c<0 || c>=COL)
        return false;
    
    return true;
}

bool matchAlgorithm::checkIfContain(const std::vector<coord>& colleciton, int r, int c)
{
    coord co;
    co.r = r;
    co.c = c;
    const std::vector<coord>::const_iterator it = std::find(colleciton.cbegin(), colleciton.cend(), co);
    if(it == colleciton.cend())
        return false;
    return true;
}



void matchAlgorithm::randomBox(colorSpriteEnum& randomEnum, std::string& spriteFrameFileName)
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

int matchAlgorithm::computeMatchBoxes(const colorSpriteEnum _rc[ROW][COL])
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
                matchAlgorithm::findSameColorsSprite(_rc,r,c,collection);
                
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

//set box grey
Sprite* matchAlgorithm::makeBoxBecomeGray(colorSpriteEnum cs)
{
    std::string s_open = "", s_close = "";
    
    switch (cs) {
        case kA:
            s_open = "s_fanqie.png";
            s_close = "s_fanqie_b.png";
            break;
            
        case kB:
            s_open = "s_lanmei.png";
            s_close = "s_lanmei_b.png";
            break;
            
        case kC:
            s_open = "s_qiezi.png";
            s_close = "s_qiezi_b.png";
            break;
            
        case kD:
            s_open = "s_tudou.png";
            s_close = "s_tudou_b.png";
            break;
            
        case kE:
            s_open = "s_xigua.png";
            s_close = "s_xigua_b.png";
            break;
            
        default:
            break;
    }
    
    auto sprite = Sprite::createWithSpriteFrameName(s_open.c_str());
    Animation* animation = Animation::create();
    
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_close));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_open));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_close));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_open));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_close));
    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_open));
    
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.8f/6.0);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    if(sprite)
    {
        sprite->stopAllActions();
        sprite->runAction(RepeatForever::create(action));
    }
    return sprite;
    
    /*GreyScaleSprite *ss = GreyScaleSprite::createSprite(s_open.c_str());
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
    }*/
    //return ss;
}

void matchAlgorithm::makeBoxRun(colorSpriteEnum rc[ROW][COL],
                                const Point boxpos[ROW][COL],
                                Sprite*  rcSprite[ROW][COL],
                                SpriteBatchNode* batchNode)
{
    //one time
    int r = CCRANDOM_0_1()*(ROW-1);
    int c = CCRANDOM_0_1()*(COL-1);
    bool ret = findOneBoxAndMakeItRun(rc, boxpos, rcSprite, batchNode, r,c);
    while (!ret)
    {
        r = CCRANDOM_0_1()*(ROW-1);
        c = CCRANDOM_0_1()*(COL-1);
        ret = findOneBoxAndMakeItRun(rc, boxpos, rcSprite, batchNode, r,c);
    }
    return;
}

bool matchAlgorithm::findOneBoxAndMakeItRun(colorSpriteEnum rc[ROW][COL],
                                            const Point boxpos[ROW][COL],
                                            Sprite*  rcSprite[ROW][COL],
                                            SpriteBatchNode* batchNode,
                                            int r, int c)
{
    bool ret = false;
    std::vector<coord> collection;
    findSameColorsSprite(rc,r,c,collection);
    if(collection.size() >= 2)
    {
        std::vector<coord>::iterator it = collection.begin();
        for(; it != collection.end(); ++it)
        {
            coord cd = *it;
            colorSpriteEnum  cs = rc[cd.r][cd.c];
            
            //left
            bool bleft = recreateOneBox(rc, boxpos, rcSprite, batchNode, cs, cd.r, cd.c-1);
            if(bleft)
                return true;
            
            //right
            bool bright = recreateOneBox(rc, boxpos, rcSprite, batchNode,cs, cd.r, cd.c+1);
            if(bright)
                return true;
            
            //top
            bool btop = recreateOneBox(rc, boxpos, rcSprite, batchNode,cs, cd.r+1, cd.c);
            if(btop)
                return true;
            
            //bottom
            bool bbottom = recreateOneBox(rc, boxpos, rcSprite, batchNode,cs, cd.r-1, cd.c);
            if(bbottom)
                return true;
        }
    }
    return ret;
}

bool matchAlgorithm::recreateOneBox(colorSpriteEnum rc[ROW][COL],
                                    const Point boxpos[ROW][COL],
                                    Sprite*  rcSprites[ROW][COL],
                                    SpriteBatchNode* batchNode, colorSpriteEnum cs, int r, int c)
{
    if(r>=0 && r<=ROW-1 && c>=0 && c<=COL-1)
    {
        if(rc[r][c] != cs)
        {
            rc[r][c] = cs;
            rcSprites[r][c]->removeFromParentAndCleanup(true);
            rcSprites[r][c] = nullptr;
            const char* spriteFileFrameName = "";
            
            switch (cs) {
                case kA:
                    spriteFileFrameName = "s_fanqie_b.png";
                    break;
                case kB:
                    spriteFileFrameName = "s_lanmei_b.png";
                    break;
                case kC:
                    spriteFileFrameName = "s_qiezi_b.png";
                    break;
                case kD:
                    spriteFileFrameName = "s_tudou_b.png";
                    break;
                case kE:
                    spriteFileFrameName = "s_xigua_b.png";
                    break;
                default:
                    break;
            }
            auto sprite = Sprite::createWithSpriteFrameName(spriteFileFrameName);
            batchNode->addChild(sprite);
            sprite->setPosition(boxpos[r][c]);
            rcSprites[r][c] = sprite;
            return true;
        }
    }
    return false;
}

const char* matchAlgorithm::boxFileName(colorSpriteEnum ce)
{
    const char* spriteFrameFileName = "";
    switch (ce) {
        case kA:
            spriteFrameFileName = "s_fanqie_b.png";
            return spriteFrameFileName;
            
        case kB:
            spriteFrameFileName = "s_lanmei_b.png";
            return spriteFrameFileName;
            
        case kC:
            spriteFrameFileName = "s_qiezi_b.png";
            return spriteFrameFileName;
            
        case kD:
            spriteFrameFileName = "s_tudou_b.png";
            return spriteFrameFileName;
            
        case kE:
            spriteFrameFileName = "s_xigua_b.png";
            return spriteFrameFileName;
            
        default:
            return spriteFrameFileName;
    }
    return "";
}

bool matchAlgorithm::checkIsHaveProps(const colorSpriteEnum rc[ROW][COL])
{
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            colorSpriteEnum cs  = rc[r][c];
            
            if(cs == kPropAutoClear ||
               cs == kPropBoomb ||
               cs == kPropSameColorBoomb ||
               
               cs == kPropCorssBoomb ||
               cs == kPropRandomBoom ||
               cs == kPropFivePlaces)
                return true;
        }
    }
    return false;
}

void matchAlgorithm::computerAttackCoords(const std::vector<coord>& inputVecs, std::vector<coord>& outputsVecs)
{
   /*
     子弹数量和消除方块数量相关
     消除3个方块，子弹为1个
     消除4,5个方块，子弹为2个
     消除6个方块，子弹为3个
     消除7,8个方块，子弹为4个
     消除9个方块，子弹为5个
     消除10个或以上的方块，子弹为6个
    */
    
    int size = inputVecs.size();
    if(size == 3)
    {
        int index = CCRANDOM_0_1()*(inputVecs.size()-1);
        coord cd = inputVecs[index];
        outputsVecs.push_back(cd);
    }
    
    else if(size ==5 || size == 4)
    {
        int index1, index2;
        index1 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        while(index1 == index2)
            index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        outputsVecs.push_back(inputVecs[index1]);
        outputsVecs.push_back(inputVecs[index2]);
    }
    
    else if(size == 6)
    {
        int index1, index2, index3;
        index1 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index1 == index2)
            index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index3 == index1 && index3 != index2)
            index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        outputsVecs.push_back(inputVecs[index1]);
        outputsVecs.push_back(inputVecs[index2]);
        outputsVecs.push_back(inputVecs[index3]);
    }
    else if(size == 7 || size == 8)
    {
        int index1, index2, index3, index4;
        
        index1 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index4 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        
        while(index1 == index2)
            index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index3 == index1 &&
              index3 == index2)
            index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index4 == index1 &&
              index4 == index2 &&
              index4 == index3 )
            index4 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        outputsVecs.push_back(inputVecs[index1]);
        outputsVecs.push_back(inputVecs[index2]);
        outputsVecs.push_back(inputVecs[index3]);
        outputsVecs.push_back(inputVecs[index4]);
    }
    else if(size == 9)
    {
        int index1, index2, index3, index4,index5;
        
        index1 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index4 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index5 = CCRANDOM_0_1()*(inputVecs.size()-1);

        while(index2 == index1)
            index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index3 == index1 &&
              index3 == index2)
            index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index4 == index1 &&
              index4 == index2 &&
              index4 == index3)
            index4 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index5 == index1 &&
              index5 == index2 &&
              index5 == index3 &&
              index5 == index4)
            
            index5 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        outputsVecs.push_back(inputVecs[index1]);
        outputsVecs.push_back(inputVecs[index2]);
        outputsVecs.push_back(inputVecs[index3]);
        outputsVecs.push_back(inputVecs[index4]);
        outputsVecs.push_back(inputVecs[index5]);
    }
    else
    {
        int index1, index2, index3, index4, index5, index6;
        index1 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index4 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index5 = CCRANDOM_0_1()*(inputVecs.size()-1);
        index6 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index2 == index1)
            index2 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index3 == index1 &&
              index3 == index2)
            index3 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index4 == index1 &&
              index4 == index2 &&
              index4 == index3)
            index4 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index5 == index1 &&
              index5 == index2 &&
              index5 == index3 &&
              index5 == index4)
            index5 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        while(index6 == index1 &&
              index6 == index2 &&
              index6 == index3 &&
              index6 == index4 &&
              index6 == index5 )
            index6 = CCRANDOM_0_1()*(inputVecs.size()-1);
        
        outputsVecs.push_back(inputVecs[index1]);
        outputsVecs.push_back(inputVecs[index2]);
        outputsVecs.push_back(inputVecs[index3]);
        outputsVecs.push_back(inputVecs[index4]);
        outputsVecs.push_back(inputVecs[index5]);
        outputsVecs.push_back(inputVecs[index6]);
    }
}

void matchAlgorithm::playClearAccount(const colorSpriteEnum rc[ROW][COL],
                                      std::vector<boxInfo>& propVecs,
                                      std::vector<coord>& randomVecs)
{
    /*
     注明：说明下，特殊方块就是战斗中出现的道具，在清算过程中，清算的过程为
     1）消除特殊方块，并且产生相应作用
     2）消除“5色刷新”特殊方块（如果有，那一定在特殊方块最后消除）
     3）消除5-10个普通方块
     */
    
    bool boolbox[ROW][COL];
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            boolbox[r][c] = false;
        }
    }
    
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            colorSpriteEnum cs = rc[r][c];
            
            if(cs == kPropAutoClear ||
               cs == kPropBoomb ||
               cs == kPropCorssBoomb ||
               cs == kPropFivePlaces ||
               cs == kPropRandomBoom ||
               cs == kPropSameColorBoomb)
            {
                boxInfo bi;
                bi.cs = cs;
                bi.r = r;
                bi.c = c;
                propVecs.push_back(bi);
                
                boolbox[r][c] = true;
            }
        }
    }
    
    int r1 = CCRANDOM_0_1()*(ROW-1);
    int c1 = CCRANDOM_0_1()*(COL-1);
    while(boolbox[r1][c1])
    {
        r1 = CCRANDOM_0_1()*(ROW-1);
        c1 = CCRANDOM_0_1()*(COL-1);
    }
    boolbox[r1][c1] = true;
    
    int r2 = CCRANDOM_0_1()*(ROW-1);
    int c2 = CCRANDOM_0_1()*(COL-1);
    while(boolbox[r2][c2])
    {
        r2 = CCRANDOM_0_1()*(ROW-1);
        c2 = CCRANDOM_0_1()*(COL-1);
    }
    boolbox[r2][c2] = true;
    
    int r3 = CCRANDOM_0_1()*(ROW-1);
    int c3 = CCRANDOM_0_1()*(COL-1);
    while(boolbox[r3][c3])
    {
        r3 = CCRANDOM_0_1()*(ROW-1);
        c3 = CCRANDOM_0_1()*(COL-1);
    }
    boolbox[r3][c3] = true;
    
    int r4 = CCRANDOM_0_1()*(ROW-1);
    int c4 = CCRANDOM_0_1()*(COL-1);
    while(boolbox[r4][c4])
    {
        r4 = CCRANDOM_0_1()*(ROW-1);
        c4 = CCRANDOM_0_1()*(COL-1);
    }
    boolbox[r4][c4] = true;
    
    int r5 = CCRANDOM_0_1()*(ROW-1);
    int c5 = CCRANDOM_0_1()*(COL-1);
    while(boolbox[r5][c5])
    {
        r5 = CCRANDOM_0_1()*(ROW-1);
        c5 = CCRANDOM_0_1()*(COL-1);
    }
    boolbox[r5][c5] = true;
    
    randomVecs.push_back(coord(r1,c1));
    randomVecs.push_back(coord(r2,c2));
    randomVecs.push_back(coord(r3,c3));
    randomVecs.push_back(coord(r4,c4));
    randomVecs.push_back(coord(r5,c5));
}

void matchAlgorithm::playAllBoxSimle(const colorSpriteEnum rc[ROW][COL], Sprite* rcSprites[ROW][COL])
{
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            auto sp = rcSprites[r][c];
            if(sp)
            {
                std::string s_open = "", s_close = "";
                colorSpriteEnum cs = rc[r][c];
                
                if(cs == kPropAutoClear ||
                   cs == kPropBoomb ||
                   cs == kPropCorssBoomb ||
                   cs == kPropFivePlaces ||
                   cs == kPropRandomBoom ||
                   cs == kPropSameColorBoomb)
                   continue;
                
                switch (cs) {
                    case kA:
                    s_open = "s_fanqie.png";
                    s_close = "s_fanqie_b.png";
                    break;
                    
                    case kB:
                    s_open = "s_lanmei.png";
                    s_close = "s_lanmei_b.png";
                    break;
                    
                    case kC:
                    s_open = "s_qiezi.png";
                    s_close = "s_qiezi_b.png";
                    break;
                    
                    case kD:
                    s_open = "s_tudou.png";
                    s_close = "s_tudou_b.png";
                    break;
                    
                    case kE:
                    s_open = "s_xigua.png";
                    s_close = "s_xigua_b.png";
                    break;
                    
                    default:
                    break;
                }
                
                //auto sprite = Sprite::createWithSpriteFrameName(s_open.c_str());
                Animation* animation = Animation::create();
                animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_close));
                animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_open));
                animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_close));
                animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_open));
                animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_close));
                animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s_open));
                
                //should last 2.8 seconds. And there are 14 frames.
                animation->setDelayPerUnit(0.8f/6.0);
                animation->setRestoreOriginalFrame(true);
                Animate* action = Animate::create(animation);
                sp->stopAllActions();
                sp->runAction(RepeatForever::create(action));
            }
        }
    }
    return;
}

void matchAlgorithm::stopBoxesSmile(const colorSpriteEnum rc[ROW][COL], Sprite* rcSprites[ROW][COL])
{
    for(int r=0; r<ROW; r++)
    {
        for(int c=0; c<COL; c++)
        {
            auto sp = rcSprites[r][c];
            if(sp)
            {
                sp->stopAllActions();
                
                
                colorSpriteEnum cs = rc[r][c];
                
                if(cs == kPropAutoClear ||
                   cs == kPropBoomb ||
                   cs == kPropCorssBoomb ||
                   cs == kPropFivePlaces ||
                   cs == kPropRandomBoom ||
                   cs == kPropSameColorBoomb)
                continue;
                
                const char* s_open  = "";
                const char* s_close = "";
                switch (cs) {
                    case kA:
                    s_open = "s_fanqie.png";
                    s_close = "s_fanqie_b.png";
                    break;
                    
                    case kB:
                    s_open = "s_lanmei.png";
                    s_close = "s_lanmei_b.png";
                    break;
                    
                    case kC:
                    s_open = "s_qiezi.png";
                    s_close = "s_qiezi_b.png";
                    break;
                    
                    case kD:
                    s_open = "s_tudou.png";
                    s_close = "s_tudou_b.png";
                    break;
                    
                    case kE:
                    s_open = "s_xigua.png";
                    s_close = "s_xigua_b.png";
                    break;
                    
                    default:
                    break;
                }
                sp->setSpriteFrame(s_close);
            }
        }
    }
}






