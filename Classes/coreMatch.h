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


class Prop;

class coreMatch : public Node
{
public:
    coreMatch();
    ~coreMatch();
    
    static coreMatch* create();
    bool init();
    
    void onTouch(Touch* touch);
    
    /**
     * Visits this node's children and draw them recursively.
     */
    virtual void visit();
    
private:
    
    //update grey sprite, show tip match boxes, and compute progress timebar and engergy bar
    void update(float delta);
    
    void loadPlist();
    void createBoxes();
    void createItemBox(int r, int c, colorSpriteEnum ce);
    
    //set one of box to be gray
    void setupGraySprite(int r, int c);
    
    //clear all grey boxes
    void clearGraySprites();
    
    //check if one touch is in one box
    void touchOneBox(cocos2d::Touch *touch);
    
    void  excuteDeadAndBornBoxes(std::vector<coord>& colleciton);
    
    void boxSequenceDead(const std::vector<coord>& vecs, Vector<FiniteTimeAction*>& actions);    
    void moveBoxes();
    
    void moveOneBox(Vector<Sprite*>& runSprites, Vector<FiniteTimeAction*>& runActions, int c);
    
    void moveRowBoxes(int c);
        
    void fucknewBox(Vector<Sprite*>& runSprites, Vector<FiniteTimeAction*>& runActions, int r, int c);
    
    cocos2d::ActionInterval* moveAction(float duration, Point pt);
    
    void boxCollectionSeqeunceMove(Vector<FiniteTimeAction*>& shitVec,
                                   const Vector<Sprite*>& sprites,
                                   const Vector<FiniteTimeAction*>& actions);
    
    void clearMatchTips();
    
    void attackMonster(int r, int c);
    
    void randomShowMatchTip();
            
    const char* getspriteFrameFileName(colorSpriteEnum ce);
    
    bool findOneBoxAndMakeItRun(int r, int c);
    
    bool recreateOneBox(colorSpriteEnum cs, int r, int c);
    
    void resetCanbeTouch();
        
    //enter game crazy status
    void enterCrazyStatus();
    
    //quit from game crazy status
    void quitCrazyStatus();
    
    void setupMotionBlur();
    
    void selectNextRenderTexture();
    
    void boxMove(Sprite* box, FiniteTimeAction* moveAction);
    
    //remove box
    void boxDie(int r, int c);
    
    CC_SYNTHESIZE(Point, _monster_Pos, monster_Pos)
    
    void playPropAutoClear(int r, int c);
    void playPropBoomb(int r, int c);
    void playPropSameColorBoomb(int r ,int c);
    void playPropCrossBoomb(int r, int c);
    void playPropRandomBoomb(int r, int c);
    void playPropFiveColorBoomb(int r, int c);
    void playNormalBox(int r, int c);
    void flashLabelTTF(const char* name, int fontsize);
private:
    SpriteBatchNode* _batchnode;
    
    ///show what the box is what kind of box
    //colorSpriteEnum _rc[ROW][COL];
    
    //show box position
    //cocos2d::Point _boxesPos[ROW][COL];
    
    //box house
    //cocos2d::Sprite* _rcSprites[ROW][COL];
    
    //grey sprites
    cocos2d::Vector<GreyScaleSprite*> _graysprites;
    
    //tip sprites
    cocos2d::Vector<Sprite*> _showTips;
    
    float _updateTime;
    float _updateGrayTime;
    float _updateTipTime;
    float _updateBarTime;
    float _updateCrazyTime;
    float _updatePropTime;
    
    bool  _canbTouch;
    bool  _bShowTip;
    
    float _continueAddTime;
    int   _continueTimes;
    
    //motion blur
    int _kRenderTextureCount;
    int _currentRenderTextureIndex;
    Vector<RenderTexture*> _renderTextures;
    
    //prop
    int _propcount;
    bool _bProduceProp;
    int _propSequence;
};

#endif
