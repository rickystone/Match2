//
//  PropBuyUI.h
//  Match
//
//  Created by 程小二 on 14-3-12.
//
//

#ifndef Match_PropBuyUI_h
#define Match_PropBuyUI_h

#include "cocos2d.h"
#include "util.h"

using namespace cocos2d;

#include "gui/CocosGUI.h"

using namespace gui;

class PropBuyUI : public Layer
{
public:
    PropBuyUI();
    ~PropBuyUI();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(PropBuyUI);
    
    bool init();
    
private:
    
    void setupPetBtn();
    void setupMonsterBtn();
    void setupExtractBtn();
    void setupFightBtn();
    
    void setupPic();
    
    void setupFirst();
    void setupListView();
    void setupScrollView();
    
    void buyButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    
    void coinButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void dimandButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void setupButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void boxButtonEvent(cocos2d::Object *pSender, TouchEventType type);

    
    void petButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void monsterButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void extractButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void fightButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    
    void selectedItemEvent(Object *pSender, ListViewEventType type);
    
private:
    void processBuy(int index);
    int computePropsProbability(int array[], int size);
    void showExtraction(const char* tipword);

    Vector<gui::Text*> _propLabelPrices;
    std::vector<colorSpriteEnum> _csVector;
};


#endif
