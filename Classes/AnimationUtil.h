//
//  AnimationUtil.h
//  Match
//
//  Created by 程小二 on 14-2-11.
//
//

#ifndef Match_AnimationUtil_h
#define Match_AnimationUtil_h

#include "cocos2d.h"
#include "gui/CocosGUI.h"

USING_NS_CC;
using namespace gui;

class AnimationUtil
{
public:
    static Animate* pauseAnimationFromFrame();
    static Button* createButton(const char* normal, const char* pressed);
    static Label* createLabel(const char* ttf, int fontsize);
};

#endif
