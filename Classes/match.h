//
//  match.h
//  MyGame
//
//  Created by ricky stone on 14-1-15.
//
//

#ifndef MyGame_match_h
#define MyGame_match_h

#include "CCLayer.h"

#include "cocos2d.h"
#include "ShaderSprite.h"
#include "gui/CocosGUI.h"

USING_NS_CC;
using namespace gui;


#define ROW 7
#define COL 7

enum  colorSpriteEnum{
     kA,
     kB,
     kC,
     kD,
     kE,
     kRabbit,
     kUnSigned,
};

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

class match :  public cocos2d::Layer
{
public:
    match();
    ~match();
    
    //static match* create();
    
    //there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    //implement the "static create()" method manually
    CREATE_FUNC(match);

    bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    //void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    //void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    //void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void detectSprite(cocos2d::Touch* touch);
    
    void findSameColorsSprite(int r, int c, std::vector<coord>& collection);
    
    void processRC(std::queue<coord>& queues, std::vector<coord>& collection, colorSpriteEnum curKc, int r, int c);
    bool checkBundary(int r, int c);
    bool checkIfContain(const std::vector<coord>& colleciton, int r, int c);
    
    void moveRowBoxes(int c);
    void moveBoxes(const std::vector<coord>& collections);
    void randomColor(cocos2d::Color3B& color3B, colorSpriteEnum& randomEnum);
    
    cocos2d::ActionInterval* moveAction(cocos2d::Point pt);
    
    void resetCanbeTouch();
    
    //显示可以匹配的随机匹配
    void randomShowMatchTip();
    
    void update(float delta);
    void setupGraySprite(int r, int c);
    
    void clearMatchTips();
    void clearGraySprites();
    
    //计算有多少个可以联系消除的
    int computeMatches();
    
    void createBoxes();
    void createItemBox(int r, int c);
    
    void moveOneBox(int c);
    
    void setupTimerProgress();
    void setupEnergyProgress();
    
    void setupMonster();
    void attackMonster(const std::vector<coord>& coords);
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    void stopBulleSpeed(cocos2d::Sprite* bullet);
    
    void computeAttack();
    void boxDeadEffect(const std::vector<coord>& collections);
    
    void createRabbit();
    
    void setupButton();
    void setupPauseButton();
    
    void touchEvent1(cocos2d::Object *pSender, TouchEventType type);
    void touchEvent2(cocos2d::Object *pSender, TouchEventType type);
    void pauseEvent(cocos2d::Object  *pSender, TouchEventType type);
    
    void popupLayer();
    void buttonCallback(cocos2d::Node *pNode);
    void addEneryBar(float percent);
    
    void petAttack();
    void setupPets();
private:
    void createRowSprites(cocos2d::Point startPt, int r);
    void createRowsSprite(cocos2d::Point start);
    Button* createButton(const char* normal, const char* pressed);
    Label* createLabel();
    
private:
    colorSpriteEnum _rc[ROW][COL];
    cocos2d::Point _boxesPos[ROW][COL];
    cocos2d::Sprite* _rcSprites[ROW][COL];
    
    cocos2d::Vector<GreyScaleSprite*> _graysprites;
    cocos2d::Vector<Sprite*> _showTips;
    cocos2d::Node* _boxParentNode;
    
    bool  _canbTouch;
    float _updateTime;
    float _updateGrayTime;
    float _updateTipTime;
    float _updateBarTime;
    bool  _bShowTip;
    
    float _timeBarPercent;
    int _timeBarLabelNum;
    
    float _energyBarPercent;
    int _energyBarLabelNum;
    
    Point _monster_Pos;
    Point _pet_Pos;
    
    PhysicsWorld* m_world;
    bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
    Point _boxbkPos;
};

#endif
