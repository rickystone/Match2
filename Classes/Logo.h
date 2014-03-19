//
//  Logo.h
//  Match
//
//  Created by 程小二 on 14-3-13.
//
//

#ifndef Match_Logo_h
#define Match_Logo_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"

using namespace gui;

class Logo : public Layer
{
public:
    Logo();
    ~Logo();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Logo);
    
    bool init();
    
private:
    void update(float delta);
    void nextscene();
};


#endif
