//
//  Prop.h
//  Match
//
//  Created by 程小二 on 14-2-25.
//
//

#ifndef Match_Prop_h
#define Match_Prop_h

#include "cocos2d.h"
#include "util.h"

USING_NS_CC;

class Prop : public Node
{
public:
    Prop();
    virtual ~Prop();
    static Prop* create();
    bool init();
    
    void setupProp();
    
    //自动胶囊
    static void propAutoBoomb(const colorSpriteEnum rc[ROW][COL], std::vector<std::vector<coord>>& cs);
    
    //炸弹胶囊
    static void propBoomb(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs, int r, int c);
    
    //同色胶囊
    static void propSameColorBoomb(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs);
    
    //十字炸弹
    static void propCrossBooomb(const colorSpriteEnum rc[ROW][COL], int r, int c, std::vector<coord>& rowVecs,std::vector<coord>& colVecs);

    //5色刷新
    static void propFiveColorSpace(colorSpriteEnum newRc[ROW][COL]);
    
    //随机炸弹
    static void propRandomBoomNBoxes(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs);
    
private:
    static void  WalkSameColor(int r, int c, bool boolbxo[ROW][COL], colorSpriteEnum newRc[ROW][COL], colorSpriteEnum curCS, int cnt);    
    static bool isProp(const colorSpriteEnum rc[ROW][COL],int r, int c);
};

#endif

