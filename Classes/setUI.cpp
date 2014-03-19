//
//  setUI.cpp
//  Match
//
//  Created by 程小二 on 14-3-16.
//
//

#include "setUI.h"
#include "mainUI.h"

Scene* setUI::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = setUI::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

setUI::setUI() {}

setUI::~setUI() {}

bool setUI::init()
{
    setup();
    return true;
}

void setUI::setup()
{
    auto s = Director::getInstance()->getWinSize();
    ImageView *setupView = ImageView::create();
    setupView->setScale9Enabled(true);
    setupView->loadTexture("UI/green_edit.png");
    setupView->setSize(Size(s.width-20, 50));
    addChild(setupView);
    setupView->setPosition(Point(setupView->getSize().width/2 + 10, s.height - setupView->getSize().height/2 - 10));
    
    //图鉴
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("设置");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    setupView->addChild(alert);
    
    
    //返回btn
    Button* backBtn = Button::create();
    backBtn->setTouchEnabled(true);
    
    //open scale9 render
    backBtn->setScale9Enabled(true);
    backBtn->loadTextures("UI/button_green_n2.png", "UI/button_green_un2.png", "");
    backBtn->setSize(Size(s.width/10, s.width/12));
    backBtn->addTouchEventListener(this, toucheventselector(setUI::backButtonEvent));
    backBtn->setPosition(Point(-setupView->getSize().width/2 + backBtn->getSize().width/2 + 10, 0));
    setupView->addChild(backBtn);
    
    alert = gui::Text::create();
    alert->setText("返回");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    backBtn->addChild(alert);
    
    ImageView *part1View = ImageView::create();
    part1View->setScale9Enabled(true);
    part1View->loadTexture("UI/green_edit.png");
    part1View->setSize(Size(s.width-20, s.height*0.5));
    addChild(part1View);
    part1View->setPosition(Point(s.width/2, setupView->getPosition().y - setupView->getSize().height/2 - 5 - part1View->getSize().height/2));
    
    //team instro
    ImageView *part2View = ImageView::create();
    part2View->setScale9Enabled(true);
    part2View->loadTexture("UI/green_edit.png");
    part2View->setSize(Size(s.width-20, s.height*0.45));
    addChild(part2View);
    part2View->setPosition(Point(s.width/2, part1View->getPosition().y - part1View->getSize().height/2 - 5 - part2View->getSize().height/2));
}

void setUI::backButtonEvent(cocos2d::Object *pSender, TouchEventType type)
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

