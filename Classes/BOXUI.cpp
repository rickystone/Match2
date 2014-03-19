//
//  BOXUI.cpp
//  Match
//
//  Created by 程小二 on 14-3-16.
//
//

#include "BOXUI.h"
#include "mainUI.h"

Scene* BOXUI::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = BOXUI::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

BOXUI::BOXUI()  {}

BOXUI::~BOXUI() {}

bool BOXUI::init()
{
    setupPic();
    return true;
}

void BOXUI::setupPic()
{
    auto s = Director::getInstance()->getWinSize();
    //金钱
    ImageView *boxView = ImageView::create();
    boxView->setScale9Enabled(true);
    boxView->loadTexture("UI/green_edit.png");
    boxView->setSize(Size(s.width-20, 50));
    addChild(boxView);
    boxView->setPosition(Point(boxView->getSize().width/2 + 10, s.height - boxView->getSize().height/2 - 10));
    
    //图鉴
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("BOX");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    boxView->addChild(alert);
    
    
    //返回btn
    Button* backBtn = Button::create();
    backBtn->setTouchEnabled(true);
    
    //open scale9 render
    backBtn->setScale9Enabled(true);
    backBtn->loadTextures("UI/button_green_n2.png", "UI/button_green_un2.png", "");
    backBtn->setSize(Size(s.width/10, s.width/12));
    backBtn->addTouchEventListener(this, toucheventselector(BOXUI::backButtonEvent));
    backBtn->setPosition(Point(-boxView->getSize().width/2 + backBtn->getSize().width/2 + 10, 0));
    boxView->addChild(backBtn);
    
    alert = gui::Text::create();
    alert->setText("返回");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    backBtn->addChild(alert);

    ///
    ImageView *stuffView1 = ImageView::create();
    stuffView1->setScale9Enabled(true);
    stuffView1->loadTexture("UI/green_edit.png");
    stuffView1->setSize(Size(s.width-20, 80));
    addChild(stuffView1);
    stuffView1->setPosition(Point(boxView->getPosition().x,
                                  boxView->getPosition().y - boxView->getSize().height/2 - stuffView1->getSize().height/2-10));
    
    alert = gui::Text::create();
    alert->setText("幸运BOX一共10级别，每级都有不同好礼物，\n      开启获得神秘礼物哦， 快快行动吧！");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    stuffView1->addChild(alert);
    
    //lv10 - lv10
    ImageView *lvView = ImageView::create();
    lvView->setScale9Enabled(true);
    lvView->loadTexture("UI/green_edit.png");
    lvView->setSize(Size(s.width/2, 80));
    addChild(lvView);
    
    lvView->setPosition(Point(s.width/2,
                              stuffView1->getPosition().y - stuffView1->getSize().height/2 - lvView->getSize().height/2 - 10));
    
    alert = gui::Text::create();
    alert->setText("lv10 - lv10");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    lvView->addChild(alert);
    
    
    //图标
    ImageView *tipView = ImageView::create();
    tipView->setScale9Enabled(true);
    tipView->loadTexture("UI/green_edit.png");
    tipView->setSize(Size(s.width/2, s.height*0.3));
    addChild(tipView);
    tipView->setPosition(Point(s.width/2, lvView->getPosition().y - lvView->getSize().height/2 - 10 - tipView->getSize().height/2));

    alert = gui::Text::create();
    alert->setText("图标");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    tipView->addChild(alert);

    //获取内容
    ImageView *hostView = ImageView::create();
    hostView->setScale9Enabled(true);
    hostView->loadTexture("UI/green_edit.png");
    hostView->setSize(Size(s.width*0.9, s.height*0.4));
    addChild(hostView);
    hostView->setPosition(Point(s.width/2, tipView->getPosition().y - tipView->getSize().height/2 - hostView->getSize().height/2));
    
    alert = gui::Text::create();
    alert->setText("获取内容");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    hostView->addChild(alert);
    
    return;
}


void BOXUI::backButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("boxui back btn event");
        
        float duration = 0.5f;
        auto layer = mainUI::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}
