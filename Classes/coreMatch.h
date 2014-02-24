//
//  coreMatch.h
//  Match
//
//  Created by 程小二 on 14-2-13.
//
//

#ifndef Match_coreMatch_h
#define Match_coreMatch_h

#include "cocos2d.h"
#include "util.h"
#include "ShaderSprite.h"

USING_NS_CC;

class coreMatch : public Node
{
public:
    coreMatch();
    ~coreMatch();
    
    static coreMatch* create();
    bool init();
    
    void onTouch(Touch* touch);
private:
    
    //update grey sprite, show tip match boxes, and compute progress timebar and engergy bar
    void update(float delta);
    
    void setBkGround();
    void createBoxes();
    void createItemBox(int r, int c);
    
    void randomColor(colorSpriteEnum& randomEnum, std::string& spriteFrameFileName);
    
    //set one of box to be gray
    void setupGraySprite(int r, int c);
    
    //clear all grey boxes
    void clearGraySprites();
    
    //check if one touch is in one box
    void touchOneBox(cocos2d::Touch *touch);
    
    //find the group of color boxes
    void findSameColorsSprite(int r, int c, std::vector<coord>& collection);
    
    //use deque to loop find same color boxes
    void processRC(std::queue<coord>& queues, std::vector<coord>& collection, colorSpriteEnum curKc, int r, int c);

    //check if out of bundary
    bool checkBundary(int r, int c);
    
    //check if 
    bool checkIfContain(const std::vector<coord>& colleciton, int r, int c);
    
    //selected box dead, burn shine effect
    void boxDeadEffect(const std::vector<coord>& collections);
    
    void moveBoxes();
    
    void moveOneBox(Vector<Sprite*>& runSprites, Vector<FiniteTimeAction*>& runActions, int c);
    
    void moveRowBoxes(int c);
    
    void bornNewBox(int c);
    
    void fucknewBox(int r, int c);
    
    cocos2d::ActionInterval* moveAction(float duration, Point pt);
    
    void clearMatchTips();
    
    void attackMonster(const std::vector<coord>& coords);
    
    void randomShowMatchTip();
    
    int computeMatchBoxes();
    
    void  makeBoxRun();
    
    const char* getspriteFrameFileName(colorSpriteEnum ce);
    
    bool findOneBoxAndMakeItRun(int r, int c);
    
    bool recreateOneBox(colorSpriteEnum cs, int r, int c);
    
    void resetCanbeTouch();
    
    void makeBoxSimle(int r, int c);
    
    //enter game crazy status
    void enterCrazyStatus();
    
    //quit from game crazy status
    void quitCrazyStatus();
    
    void createShowTipParticl(int r, int c);
    
    CC_SYNTHESIZE(Point, _monster_Pos, monster_Pos)
    
private:
    SpriteBatchNode* _batchnode;
    
    ///show what the box is what kind of box
    colorSpriteEnum _rc[ROW][COL];
    
    //show box position
    cocos2d::Point _boxesPos[ROW][COL];
    
    //box house
    cocos2d::Sprite* _rcSprites[ROW][COL];
    
    //grey sprites
    cocos2d::Vector<GreyScaleSprite*> _graysprites;
    
    //tip sprites
    cocos2d::Vector<Sprite*> _showTips;
    
    float _updateTime;
    float _updateGrayTime;
    float _updateTipTime;
    float _updateBarTime;
    float _updateCrazyTime;
    
    bool  _canbTouch;
    bool  _bShowTip;
    
    float _continueAddTime;
    int   _continueTimes;
};
#endif
