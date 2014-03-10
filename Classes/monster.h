//
//  monster.h
//  Match
//
//  Created by 程小二 on 14-2-15.
//
//

#ifndef Match_monster_h
#define Match_monster_h

#include "cocos2d.h"
#include "gui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;


class monster : public cocos2d::Node
{
public:
    monster();
    ~monster();
    static monster* create();
    bool init();
    
    CC_SYNTHESIZE(cocos2d::Point, _monster_pos, monster_pos);
    
    void hurt();    
private:
    void setupMonster();
    Armature*  _pMonsterArmature;
};

#endif
