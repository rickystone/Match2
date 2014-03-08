//
//  matchAlgorithm.h
//  Match
//
//  Created by 程小二 on 14-2-25.
//
//

#ifndef Match_matchAlgorithm_h
#define Match_matchAlgorithm_h

#include "util.h"
#include <vector>
#include <queue>
#include "cocos2d.h"

USING_NS_CC;


class GreyScaleSprite;

class matchAlgorithm
{
public:
    matchAlgorithm();
    ~matchAlgorithm();
    
    static void findSameColorsSprite(const colorSpriteEnum _rc[ROW][COL], int r, int c, std::vector<coord>& collection);
    static void randomBox(colorSpriteEnum& randomEnum, std::string& spriteFrameFileName);
    static int  computeMatchBoxes(const colorSpriteEnum _rc[ROW][COL]);
    
    static GreyScaleSprite* makeBoxBecomeGray(colorSpriteEnum cs);
    
    static void makeBoxRun(colorSpriteEnum rc[ROW][COL],
                    const Point boxpos[ROW][COL],
                    Sprite* rcSprite[ROW][COL],
                    SpriteBatchNode* batchNode);
    
    
    static bool findOneBoxAndMakeItRun(colorSpriteEnum rc[ROW][COL],
                                const Point boxpos[ROW][COL],
                                Sprite*  rcSprite[ROW][COL],
                                SpriteBatchNode* batchNode,
                                int r, int c);
    
    static bool recreateOneBox(colorSpriteEnum rc[ROW][COL],
                        const Point boxpos[ROW][COL],
                        Sprite*  rcSprites[ROW][COL],
                        SpriteBatchNode* batchNode, colorSpriteEnum cs, int r, int c);

    
    static const char* boxFileName(colorSpriteEnum ce);
    
private:
    static void processRC(const colorSpriteEnum _rc[ROW][COL], std::queue<coord>& queues, std::vector<coord>& collection,
                   colorSpriteEnum curKc, int r, int c);
    static bool checkBundary(int r, int c);
    static bool checkIfContain(const std::vector<coord>& colleciton, int r, int c);
};

#endif
