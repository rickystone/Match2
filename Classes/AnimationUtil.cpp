//
//  AnimationUtil.cpp
//  Match
//
//  Created by 程小二 on 14-2-11.
//
//

#include "AnimationUtil.h"

Animate* AnimationUtil::pauseAnimationFromFrame()
{
    Animation* animation = Animation::create();
    for(int i=1;i<15;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "Images/grossini_dance_%02d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 14.0f);
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
