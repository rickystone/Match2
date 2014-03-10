//
//  util.h
//  Match
//
//  Created by 程小二 on 14-2-12.
//
//

#ifndef Match_util_h
#define Match_util_h

#define ROW 7
#define COL 7

#define CRAZYTIME  2
#define CRAZYCOUNT 7

#define CRAZTBURNTIME 5

#define MOVEDURATION  0.1
#define PARTICLEDURATION 0.2
#define BOXDEADDURATION  0.02

#define BOXSCALEDURATION  0.3

//产生子弹的间隔时间
#define BLLUETSTEPTIME 0.25f

//子弹特效动画时间
#define  BULLETFRAMEANIMATIONTIEM 0.08

#define random_range(low,high) (arc4random()%(high-low+1))+low
#define frandom (float)arc4random()/UINT64_C(0x100000000)
#define frandom_range(low,high) ((high-low)*frandom)+low

#include "cocos2d.h"

enum  colorSpriteEnum{
    
    kA,                   //元素A
    kB,                   //元素B
    kC,                   //元素C
    kD,                   //元素D
    kE,                   //元素E
    
    kPropAutoClear,       //自动胶囊
    kPropBoomb,           //炸弹胶囊
    kPropSameColorBoomb,  //同色胶囊
    
    kPropCorssBoomb,      //十字炸弹
    kPropRandomBoom,      //随机炸弹
    kPropFivePlaces,      //5色刷新
    
    kUnSigned,
};

typedef enum {
    NORMAL_STATE,
    CRAZY_STATE,
} game_state;

typedef enum {
    kBoxBk = 0,
    kBatchNode,
    kCrazyEffect,
} coreMatchTag;

typedef enum {
    kMonster,
    kMonsterHp,
} monster_enum;

typedef enum {
    kFirstBack,
    kTimerBar,
    kEnergyBar,
}match_enum;

typedef enum {
    kPet,
}pet_enum;

typedef struct coord
{
    int r, c;
    coord(int _r=0, int _c=0) : r(_r), c(_c) {}
    bool operator==(const coord& right) const
    {
        if(r == right.r && c == right.c)
            return true;
        return false;
    }
} coord;

typedef struct boxInfo
{
    int r;
    int c;
    colorSpriteEnum cs;
} boxInfo;


#endif
