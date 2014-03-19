//
//  AnimationUtil.cpp
//  Match
//
//  Created by 程小二 on 14-2-11.
//
//

#include "AnimationUtil.h"

Animate* AnimationUtil::createAnimateFromFile(const char* filename, int count, float unitTime)
{
    Animation* animation = Animation::create();
    for(int i=1; i<=count; i++)
    {
        char szname[100] = {0};
        std::string ss = filename;
        ss += "_%01d.png";
        sprintf(szname, ss.c_str(), i);
        animation->addSpriteFrameWithFile(szname);
    }
    animation->setDelayPerUnit(unitTime);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    return action;
}

Animate* AnimationUtil::createAnimateFromFrame(const char* filename, int count, float unitTime)
{
    Animation* animation = Animation::create();
    for(int i=1; i<=count; i++)
    {
        char szname[100] = {0};
        std::string ss = filename;
        ss += "_%01d.png";
        sprintf(szname, ss.c_str(), i);
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szname));
    }
    animation->setDelayPerUnit(unitTime);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    return action;
}

Button* AnimationUtil::createButton(const char* normal, const char* pressed)
{
    Button* button = Button::create();
    button->setTouchEnabled(true);
    button->loadTextures(normal, pressed, "");
    return button;
}

Label* AnimationUtil::createLabel(const char* ttf, int fontsize)
{
    auto s = Director::getInstance()->getWinSize();
    //TTFConfig ttfConfig("fonts/arial.ttf", fontsize, GlyphCollection::DYNAMIC, nullptr, true);
    TTFConfig ttfConfig(ttf, fontsize, GlyphCollection::DYNAMIC, nullptr, true);
    auto label = Label::createWithTTF(ttfConfig,"",TextHAlignment::CENTER,s.width);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setColor(Color3B::WHITE);
    return label;
}

