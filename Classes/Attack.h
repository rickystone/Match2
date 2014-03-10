//
//  Attack.h
//  Match
//
//  Created by 程小二 on 14-2-16.
//
//

#ifndef Match_Attack_h
#define Match_Attack_h

#include "cocos2d.h"
USING_NS_CC;


class Attack : public Node
{
public:
    Attack();
    ~Attack();
    bool init();
    static Attack* create();
    
    void shootBullet(int r, int c,  Point destinationk, Point startPoint);
    void killMe();
};

#endif
