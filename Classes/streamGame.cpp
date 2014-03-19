//
//  streamGame.cpp
//  Match
//
//  Created by 程小二 on 14-3-15.
//
//

#include "streamGame.h"
using namespace cocos2d;

void streamGame::writeGame(const colorSpriteEnum rc[ROW][COL])
{
    for(int r = 0; r<ROW; r++)
    {
        for(int c=0; c<COL; c++)
        {
            colorSpriteEnum cs = rc[r][c];
            char buf[10];
            
            sprintf(buf, "%d", r);
            std::string key = "";
            key = buf;
            key += "_";
            
            sprintf(buf, "%d", c);
            key += buf;
            key += "_integer";
            
            cocos2d::UserDefault::getInstance()->setIntegerForKey(key.c_str(), (int)cs);
        }
    }
    UserDefault::getInstance()->flush();
}

void streamGame::readGame(colorSpriteEnum rc[ROW][COL])
{
    for(int r=0; r<ROW; r++)
    {
        for(int c=0; c<COL; c++)
        {
            char buf[10];
            sprintf(buf, "%d", r);
            std::string key = "";
            key = buf;
            key += "_";
            
            sprintf(buf, "%d", c);
            key += buf;
            key += "_integer";
            
            colorSpriteEnum cs = (colorSpriteEnum)UserDefault::getInstance()->getIntegerForKey(key.c_str());
            
            rc[r][c] = cs;
        }
    }
}
