
//
//  PropUI.h
//  Match
//
//  Created by 程小二 on 14-2-26.
//
//

#ifndef Match_PropUI_h
#define Match_PropUI_h

#include "cocos2d.h"
using namespace cocos2d;

class PropUI : public Layer
{
public:
    PropUI();
    ~PropUI();
    static PropUI* create();
    bool init();
};

#endif
