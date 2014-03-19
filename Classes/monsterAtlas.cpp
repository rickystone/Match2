//
//  monsterAtlas.cpp
//  Match
//
//  Created by 程小二 on 14-3-15.
//
//

#include "monsterAtlas.h"
#include "mainUI.h"

#define  ViewH 210

Scene* monsterAtlas::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = monsterAtlas::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

monsterAtlas::monsterAtlas() : _idx(0) {}

monsterAtlas::~monsterAtlas() {}

bool monsterAtlas::init()
{
    auto s = Director::getInstance()->getWinSize();
    setupListView();
    setupLeast();
    return true;
}

void monsterAtlas::setupLeast()
{
    auto s = Director::getInstance()->getWinSize();
    
    ImageView* view = ImageView::create();
    view->setScale9Enabled(true);
    view->loadTexture("UI/dipang.png");
    view->setSize(Size(s.width/2-20, 50));
    addChild(view);
    
    gui::Text* alert = gui::Text::create();
    alert->setText("星星9999999");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    view->addChild(alert);
    
    auto layercolor = (LayerColor*)this->getChildByTag(0);
    auto backsize = layercolor->getContentSize();
    view->setPosition(Point(view->getSize().width/2 + 10, backsize.height + view->getSize().height/2 + 10));
    
    ImageView *view2 = ImageView::create();
    view2->setScale9Enabled(true);
    view2->loadTexture("UI/dipang.png");
    view2->setSize(Size(s.width/2-20, 50));
    addChild(view2);
    view2->setPosition(Point(view->getPosition().x + view->getSize().width + 10, view->getPosition().y));

    alert = gui::Text::create();
    alert->setText("皇冠*10(+100%)");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    view2->addChild(alert);
    
    //图鉴
    ImageView *view3 = ImageView::create();
    view3->setScale9Enabled(true);
    view3->loadTexture("UI/dipang.png");
    view3->setSize(Size(s.width-10, 50));
    view3->setPosition(Point(s.width/2, view2->getPosition().y + view2->getSize().height + 10));
    addChild(view3);
    
    alert = gui::Text::create();
    alert->setText("图鉴");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    view3->addChild(alert);
    
    //返回btn
    Button* backBtn = Button::create();
    backBtn->setTouchEnabled(true);
    
    //open scale9 render
    backBtn->setScale9Enabled(true);
    backBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    backBtn->setSize(Size(s.width/10, s.width/12));
    backBtn->addTouchEventListener(this, toucheventselector(monsterAtlas::backButtonEvent));
    backBtn->setPosition(Point(-view3->getSize().width/2 + backBtn->getSize().width/2 + 10, 0));
    view3->addChild(backBtn);
    
    alert = gui::Text::create();
    alert->setText("返回");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    backBtn->addChild(alert);

    //金钱
    ImageView *moneyView = ImageView::create();
    moneyView->setScale9Enabled(true);
    moneyView->loadTexture("UI/dipang.png");
    moneyView->setSize(Size(s.width*0.35, 50));
    addChild(moneyView);
    moneyView->setPosition(Point(moneyView->getSize().width/2 + 20, view3->getPosition().y + view3->getSize().height + 10));
    
    
    alert = gui::Text::create();
    alert->setText("金钱999999");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    moneyView->addChild(alert);

    //+
    Button* addBtn = Button::create();
    addBtn->setTouchEnabled(true);
    addBtn->setScale9Enabled(true);
    addBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    addBtn->setSize(Size(s.width/10, s.width/12));
    addBtn->addTouchEventListener(this, toucheventselector(monsterAtlas::coinButtonEvent));
    addChild(addBtn);
    addBtn->setPosition(Point(moneyView->getPosition().x + moneyView->getSize().width/2 + 10 + addBtn->getSize().width/2,
                              moneyView->getPosition().y));
    //宝石
    ImageView *dimandView = ImageView::create();
    dimandView->setScale9Enabled(true);
    dimandView->loadTexture("UI/dipang.png");
    dimandView->setSize(Size(s.width*0.35, 50));
    addChild(dimandView);
    dimandView->setPosition(Point(addBtn->getPosition().x + addBtn->getSize().width/2 + 10 + dimandView->getSize().width/2,
                                  addBtn->getPosition().y));
    
    
    alert = gui::Text::create();
    alert->setText("宝石999999");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    dimandView->addChild(alert);
    
    //+
    Button* baoshiBtn = Button::create();
    baoshiBtn->setTouchEnabled(true);
    baoshiBtn->setScale9Enabled(true);
    baoshiBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    baoshiBtn->setSize(Size(s.width/10, s.width/12));
    baoshiBtn->addTouchEventListener(this, toucheventselector(monsterAtlas::dimandButtonEvent));
    addChild(baoshiBtn);
    baoshiBtn->setPosition(Point(dimandView->getPosition().x + dimandView->getSize().width/2 + 10 + baoshiBtn->getSize().width/2,
                                 dimandView->getPosition().y));
}

void monsterAtlas::setupListView()
{
    auto s = Director::getInstance()->getWinSize();
    auto layercolor = LayerColor::create(Color4B(100,100,100,200), s.width, s.height*0.8);
    addChild(layercolor,0,0);
    layercolor->setPosition(Point(0,0));
    layercolor->setAnchorPoint(Point(0,0));
    auto backsize = layercolor->getContentSize();
    
    //Create the list view ex
    ListView* listView = ListView::create();
    //set list view ex direction
    listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);
    listView->setBackGroundImage("UI/dipang.png");
    listView->setBackGroundImageScale9Enabled(true);
    
    listView->setSize(Size(backsize.width-10, backsize.height*0.95));
    
    listView->setPosition(Point((s.width - backsize.width) / 2.0f +
                                (backsize.width - listView->getSize().width) / 2.0f,
                                (backsize.height - listView->getSize().height) / 2.0f));
    
    //istView->addEventListenerListView(this, listvieweventselector(monsterAtlas::selectedItemEvent));
    this->addChild(listView);
    
    ImageView* default_view = ImageView::create();
    default_view->setScale9Enabled(true);
    default_view->loadTexture("UI/dipang.png");
    default_view->setSize(Size(listView->getSize().width, ViewH));
    this->setupViews(default_view);
    
    Layout* default_item = Layout::create();
    default_item->setTouchEnabled(true);
    default_item->setSize(default_view->getSize());
    default_view->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
    default_item->addChild(default_view);
    listView->pushBackCustomItem(default_item);
    
    //set model
    listView->setItemModel(default_item);
    
    // add custom item
    for (size_t i = 0; i < 10; ++i)
    {
        ImageView* default_view = ImageView::create();
        default_view->setScale9Enabled(true);
        default_view->loadTexture("UI/dipang.png");
        default_view->setSize(Size(listView->getSize().width, ViewH));
        this->setupViews(default_view);
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setSize(default_view->getSize());
        default_view->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
        default_item->addChild(default_view);
        listView->pushBackCustomItem(default_item);
    }
    
    //set all items layout gravity
    listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
    
    //set items margin
    listView->setItemsMargin(2.0f);
}

void monsterAtlas::setupViews(ImageView* parentView)
{
    ImageView* v1 = setupAtlas(1, _idx++);
    ImageView* v2 = setupAtlas(2, _idx++);
    ImageView* v3 = setupAtlas(3, _idx++);
    ImageView* v4 = setupAtlas(4, _idx++);
    
    parentView->addChild(v1);
    parentView->addChild(v2);
    parentView->addChild(v3);
    parentView->addChild(v4);
    
    v1->setPosition(Point(20+v1->getSize().width/2 - parentView->getSize().width/2,20));
    v2->setPosition(Point(v1->getPosition().x + v1->getSize().width/2 + v2->getSize().width/2 + 10, 20));
    v3->setPosition(Point(v2->getPosition().x + v2->getSize().width/2 + v3->getSize().width/2 + 10, 20));
    v4->setPosition(Point(v3->getPosition().x + v3->getSize().width/2 + v4->getSize().width/2 + 10, 20));
}

ImageView* monsterAtlas::setupAtlas(int lv,int idx)
{
    auto s = Director::getInstance()->getWinSize();
    int viewWidth =  s.width/4 - 20;
    ImageView* atlasView = ImageView::create();
    atlasView->setScale9Enabled(true);
    atlasView->loadTexture("UI/dipang.png");
    atlasView->setSize(Size(viewWidth,viewWidth));
    
    //Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("怪物图鉴");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    atlasView->addChild(alert);
    
    //add lvView
    ImageView* lvView = ImageView::create();
    lvView->setScale9Enabled(true);
    lvView->loadTexture("UI/dipang.png");
    lvView->setSize(Size(viewWidth/3,viewWidth/6));
    atlasView->addChild(lvView);
    lvView->setPosition(Point(0, -atlasView->getSize().height/2 + lvView->getSize().height/2+10));
    
    char buf[10];
    sprintf(buf, "%d", lv);
    std::string str_lv = "lv";
    str_lv += lv;
    
    alert = gui::Text::create();
    alert->setText(str_lv.c_str());
    alert->setFontName("Marker Felt");
    alert->setFontSize(20);
    alert->setColor(Color3B::BLACK);
    lvView->addChild(alert);
    
    //add star btn
    Button* starBtn = Button::create();
    starBtn->setTouchEnabled(true);
    
    //open scale9 render
    starBtn->setScale9Enabled(true);
    starBtn->loadTextures("UI/button_01.png", "UI/button_02.png", "");
    starBtn->setSize(Size(viewWidth, viewWidth/3));
    starBtn->addTouchEventListener(this, toucheventselector(monsterAtlas::atlasButtonEvent));
    atlasView->addChild(starBtn);
    starBtn->setPosition(Point(0, -atlasView->getSize().height/2-starBtn->getSize().height/2-2));
    starBtn->setTag(idx);
    
    //add word
    //Add the alert
    alert = gui::Text::create();
    alert->setText("星星数量");
    alert->setFontName("Marker Felt");
    alert->setFontSize(25);
    alert->setColor(Color3B::BLACK);
    starBtn->addChild(alert);
    return atlasView;
}

void monsterAtlas::atlasButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        auto  btn = (Button*)pSender;
        int idx  = btn->getTag();
        CCLOG("fuck idx:%d", idx);
    }
}

void monsterAtlas::backButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        CCLOG("back button event");
        float duration = 0.5f;
        auto layer = mainUI::createScene();
        auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
        if (scene)
        {
            Director::getInstance()->replaceScene(scene);
        }
    }
}

void monsterAtlas::coinButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
}

void monsterAtlas::dimandButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
}


void monsterAtlas::selectedItemEvent(Object *pSender, ListViewEventType type)
{
    switch (type)
    {
        case LISTVIEW_ONSELECTEDITEM:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CCLOG("select child index = %ld", listView->getCurSelectedIndex());
        }
            break;
            
        default:
            break;
    }
}

