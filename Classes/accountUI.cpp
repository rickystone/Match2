//
//  accountUI.cpp
//  Match
//
//  Created by 程小二 on 14-3-16.
//
//

#include "accountUI.h"
#include "mainUI.h"

Scene* accountUI::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = accountUI::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

accountUI::accountUI() {}

accountUI::~accountUI() {}

bool accountUI::init()
{
    setup();
    return true;
}

void accountUI::setup()
{
    auto s = Director::getInstance()->getWinSize();
    
    
    ImageView* back = ImageView::create();
    back->setScale9Enabled(true);
    back->loadTexture("UI/beijing-s9.png");
    back->setSize(Size(s.width, s.height));
    back->setPosition(Point(s.width/2,s.height/2));
    this->addChild(back);

    
    ImageView *scoreView = ImageView::create();
    scoreView->setScale9Enabled(true);
    scoreView->loadTexture("UI/dipang.png");
    scoreView->setSize(Size(s.width*0.35, 50));
    scoreView->setPosition(Point(s.width/2,s.height - scoreView->getSize().height/2 - 20));
    addChild(scoreView);
    
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("成绩");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    scoreView->addChild(alert);
    
    ImageView *part1View = ImageView::create();
    part1View->setScale9Enabled(true);
    part1View->loadTexture("UI/dipang.png");
    part1View->setSize(Size(s.width*0.9, s.height*0.76f));
    addChild(part1View);
    part1View->setPosition(Point(s.width/2,
                                 scoreView->getPosition().y - scoreView->getSize().height/2 - 10 - part1View->getSize().height/2));
    
    /////////////////
    int normalH = (part1View->getSize().height -  9*10)/8;
    
    //积分
    ImageView *a1View = ImageView::create();
    a1View->setScale9Enabled(true);
    a1View->loadTexture("UI/dipang.png");
    a1View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a1View);
    a1View->setPosition(Point(0, part1View->getSize().height/2 - a1View->getSize().height/2 - 10));
    
    alert = gui::Text::create();
    alert->setText("积分");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a1View->addChild(alert);
    
    //最好成绩
    ImageView *a2View = ImageView::create();
    a2View->setScale9Enabled(true);
    a2View->loadTexture("UI/dipang.png");
    a2View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a2View);
    a2View->setPosition(Point(0,a1View->getPosition().y - a1View->getSize().height/2 - 10 - a2View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("最好成绩");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a2View->addChild(alert);

    //战斗积分
    ImageView *a3View = ImageView::create();
    a3View->setScale9Enabled(true);
    a3View->loadTexture("UI/dipang.png");
    a3View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a3View);
    a3View->setPosition(Point(0,a2View->getPosition().y - a2View->getSize().height/2 - 10 - a3View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("战斗积分");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a3View->addChild(alert);
    
    //皇冠加成
    ImageView *a4View = ImageView::create();
    a4View->setScale9Enabled(true);
    a4View->loadTexture("UI/dipang.png");
    a4View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a4View);
    a4View->setPosition(Point(0,a3View->getPosition().y - a3View->getSize().height/2 - 10 - a4View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("皇冠加成");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a4View->addChild(alert);
    
    //杀死怪物数量
    
    ImageView *a5View = ImageView::create();
    a5View->setScale9Enabled(true);
    a5View->loadTexture("UI/dipang.png");
    a5View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a5View);
    a5View->setPosition(Point(0,a4View->getPosition().y - a4View->getSize().height/2 - 10 - a5View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("杀死怪物数量");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a5View->addChild(alert);
    
    //获得金钱
    ImageView *a6View = ImageView::create();
    a6View->setScale9Enabled(true);
    a6View->loadTexture("UI/dipang.png");
    a6View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a6View);
    a6View->setPosition(Point(0,a5View->getPosition().y - a5View->getSize().height/2 - 10 - a6View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("获得金钱");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a6View->addChild(alert);

    //获得星星
    
    ImageView *a7View = ImageView::create();
    a7View->setScale9Enabled(true);
    a7View->loadTexture("UI/dipang.png");
    a7View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a7View);
    a7View->setPosition(Point(0,a6View->getPosition().y - a6View->getSize().height/2 - 10 - a7View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("获得星星");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a7View->addChild(alert);

    //获得晶石
    
    ImageView *a8View = ImageView::create();
    a8View->setScale9Enabled(true);
    a8View->loadTexture("UI/dipang.png");
    a8View->setSize(Size(part1View->getSize().width*0.8, normalH));
    part1View->addChild(a8View);
    a8View->setPosition(Point(0,a7View->getPosition().y - a7View->getSize().height/2 - 10 - a8View->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("获得晶石");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    a8View->addChild(alert);
    
    //再来一次
    Button* repeatBtn = Button::create();
    repeatBtn->setTouchEnabled(true);
    //open scale9 render
    repeatBtn->setScale9Enabled(true);
    repeatBtn->loadTextures("UI/button_01.png", "UI/button_02.png", "");
    repeatBtn->setSize(Size(s.width*0.45, 130));
    repeatBtn->addTouchEventListener(this, toucheventselector(accountUI::repeatButtonEvent));
    addChild(repeatBtn);
    repeatBtn->setPosition(Point(repeatBtn->getSize().width/2 + 20, repeatBtn->getSize().height/2 + 10));
    
    alert = gui::Text::create();
    alert->setText("再来一次");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    repeatBtn->addChild(alert);

    //回主界面
    
    Button*  backToMainUIBtn = Button::create();
    backToMainUIBtn->setTouchEnabled(true);
    //open scale9 render
    backToMainUIBtn->setScale9Enabled(true);
    backToMainUIBtn->loadTextures("UI/button_01.png", "UI/button_02.png", "");
    backToMainUIBtn->setSize(Size(s.width*0.45, 130));
    backToMainUIBtn->addTouchEventListener(this, toucheventselector(accountUI::backToMainUIButtonEvent));
    addChild(backToMainUIBtn);
    backToMainUIBtn->setPosition(Point(repeatBtn->getPosition().x + repeatBtn->getSize().width + 30,  repeatBtn->getPosition().y));
    
    alert = gui::Text::create();
    alert->setText("回主界面");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    backToMainUIBtn->addChild(alert);
}

void accountUI::repeatButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        
    }
}

void accountUI::backToMainUIButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        float duration = 0.5f;
        auto layer = mainUI::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}


