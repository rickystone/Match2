//
//  monsterAtlas.h
//  Match
//
//  Created by 程小二 on 14-3-15.
//
//

#ifndef Match_monsterAtlas_h
#define Match_monsterAtlas_h

#include "cocos2d.h"
using namespace cocos2d;

#include "gui/CocosGUI.h"
using namespace gui;

class monsterAtlas : public Layer
{
public:
    monsterAtlas();
    ~monsterAtlas();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(monsterAtlas);
    bool init();
    
private:
    
    void setupLeast();
    ImageView* setupAtlas(int lv, int idx);
    
    void setupViews(ImageView* parentView);
    void setupListView();
    
    void coinButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void dimandButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    
    void backButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void atlasButtonEvent(cocos2d::Object *pSender, TouchEventType type);
    void selectedItemEvent(Object *pSender, ListViewEventType type);
    
private:
    int _idx;
};

#endif
