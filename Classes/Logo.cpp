//
//  Logo.cpp
//  Match
//
//  Created by 程小二 on 14-3-13.
//
//

#include "Logo.h"
#include "mainUI.h"

Scene* Logo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = Logo::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

Logo::Logo() {}

Logo::~Logo() {}

bool Logo::init()
{
    auto s = Director::getInstance()->getWinSize();
    
    ImageView *background = ImageView::create();
    background->setScale9Enabled(true);
    background->loadTexture("UI/beijing-s9.png");
    background->setSize(Size(s.width,s.height));
    addChild(background);
    background->setPosition(Point(s.width/2,s.height/2));

    auto back = Sprite::create("UI/tuijintiao1.png");
    addChild(back,0,0);
    
    back->setPosition(Point(s.width/2, 100));
    
    //loading bar
    LoadingBar* loadingBar = LoadingBar::create();
    loadingBar->setTag(0);
    loadingBar->loadTexture("UI/tuijintiao2.png");
    loadingBar->setDirection(LoadingBarTypeLeft);
    loadingBar->setPercent(0);
    back->addChild(loadingBar,0,0);
    loadingBar->setPosition(Point(back->getContentSize().width/2, back->getContentSize().height/2));
    
    //setup label word
    TTFConfig ttfConfig("fonts/arial.ttf", 60, GlyphCollection::DYNAMIC,nullptr,true);
    auto label = Label::createWithTTF(ttfConfig,"",TextHAlignment::CENTER,s.width);
    label->setColor( Color3B::WHITE );
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    back->addChild(label,0,1);
    label->setPosition(Point(back->getContentSize().width/2, back->getContentSize().height/2));
    
    label->setString("Loading");
    
    scheduleUpdate();
    
    return true;
}

void Logo::update(float dt)
{
    auto back = this->getChildByTag(0);
    auto loadingbar = (LoadingBar*)back->getChildByTag(0);
    auto label = (Label*)back->getChildByTag(1);
    
    int curpercent = loadingbar->getPercent();
    curpercent += 1;
    
    loadingbar->setPercent(curpercent);
    char buf[10];
    sprintf(buf, "%d", curpercent);
    label->setString(buf);
    
    if(curpercent >= 100)
    {
        nextscene();
        unscheduleUpdate();
    }
}

void Logo::nextscene()
{
    float duration = 0.5f;
    auto layer = mainUI::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}
