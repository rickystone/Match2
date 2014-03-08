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
GreyScaleSprite* matchAlgorithm::makeBoxBecomeGray(colorSpriteEnum cs)
{
    std::string s_open = "", s_close = "";
    
    switch (cs) {
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
    return ss;
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

