//
//  PropBuyUI.cpp
//  Match
//
//  Created by 程小二 on 14-3-12.
//
//

#include "PropBuyUI.h"
#include "match.h"
#include "BOXUI.h"
#include "setUI.h"
#include "monsterAtlas.h"

Scene* PropBuyUI::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    //'layer' is an autorelease object
    auto layer = PropBuyUI::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

PropBuyUI::PropBuyUI() {}

PropBuyUI::~PropBuyUI() {}

bool PropBuyUI::init()
{
    setupPic();
    return true;
}

void PropBuyUI::setupPic()
{
    auto s = Director::getInstance()->getWinSize();
    ImageView *background = ImageView::create();
    background->setScale9Enabled(true);
    background->loadTexture("UI/beijing-s9.png");
    background->setSize(Size(s.width,s.height));
    addChild(background);
    background->setPosition(Point(s.width/2,s.height/2));
    
    auto layercolor = LayerColor::create(Color4B(100,100,100,50), s.width, s.height*0.6);
    addChild(layercolor,0,0);
    layercolor->setPosition(Point(0,200));
    
    
    setupFirst();
    setupListView();
    
    setupPetBtn();
    setupMonsterBtn();
    setupExtractBtn();
    setupFightBtn();
    return;
}


void PropBuyUI::setupPetBtn()
{
    const char* normal = "UI/button_01.png";
    const char* pressed = "UI/button_02.png";
    
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("宠物");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    
    // Create the button
    Button* button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*2, button->getContentSize().height));
    button->setPosition(Point(button->getContentSize().width+20,button->getContentSize().height/2 + 10));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(PropBuyUI::petButtonEvent));
    this->addChild(button);

}

void PropBuyUI::setupMonsterBtn()
{
    const char* normal = "UI/button_01.png";
    const char* pressed = "UI/button_02.png";
    
    auto s = Director::getInstance()->getWinSize();
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("怪物");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    
    // Create the button
    Button* button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*2, button->getContentSize().height));
    button->setPosition(Point(s.width-button->getContentSize().width-20,button->getContentSize().height/2 + 10));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(PropBuyUI::monsterButtonEvent));
    this->addChild(button);
}

void PropBuyUI::setupFightBtn()
{
    const char* normal = "UI/button_01.png";
    const char* pressed = "UI/button_02.png";
    
    auto s = Director::getInstance()->getWinSize();
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("开始战斗");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    
    // Create the button
    Button* button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*3, button->getContentSize().height));
    button->setPosition(Point(s.width/2,button->getContentSize().height/2 + 10));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(PropBuyUI::fightButtonEvent));
    this->addChild(button);
}

void PropBuyUI::setupExtractBtn()
{
    const char* normal = "UI/button_01.png";
    const char* pressed = "UI/button_02.png";
    
    auto s = Director::getInstance()->getWinSize();
    // Add the alert
    gui::Text* alert = gui::Text::create();
    alert->setText("抽取道具");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    
    // Create the button
    Button* button = Button::create();
    button->setTouchEnabled(true);
    // open scale9 render
    button->setScale9Enabled(true);
    button->loadTextures(normal, pressed, "");
    button->setSize(Size(button->getContentSize().width*3, button->getContentSize().height*0.6));
    button->setPosition(Point(s.width/2,150));
    button->addChild(alert);
    button->addTouchEventListener(this, toucheventselector(PropBuyUI::extractButtonEvent));
    this->addChild(button);
}

void PropBuyUI::setupScrollView()
{
    
    auto layercolor = (LayerColor*)this->getChildByTag(0);
    auto backsize = layercolor->getContentSize();
    auto s = Director::getInstance()->getWinSize();
    // Create the scrollview by vertical
    gui::ScrollView* scrollView = gui::ScrollView::create();
    scrollView->setTouchEnabled(true);
    
    scrollView->setSize(Size(backsize.width-10, backsize.height*0.95));
    scrollView->setPosition(Point((s.width - backsize.width) / 2.0f +
                                (backsize.width - scrollView->getSize().width) / 2.0f,
                                
                                (s.height - backsize.height) / 2.0f + 5 +
                                (backsize.height - scrollView->getSize().height) / 2.0f));
    
    auto sp = Sprite::create("daojubiaoqian.png");
    scrollView->addChild(sp);

}

void PropBuyUI::setupFirst()
{
    auto s = Director::getInstance()->getWinSize();
    //金钱
    ImageView *moneyView = ImageView::create();
    moneyView->setScale9Enabled(true);
    moneyView->loadTexture("UI/dipang.png");
    moneyView->setSize(Size(s.width*0.35, 50));
    addChild(moneyView);
    moneyView->setPosition(Point(moneyView->getSize().width/2 + 20, s.height - moneyView->getSize().height/2 - 10));
    
    
    gui::Text* alert = gui::Text::create();
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
    addBtn->addTouchEventListener(this, toucheventselector(PropBuyUI::coinButtonEvent));
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
    baoshiBtn->addTouchEventListener(this, toucheventselector(PropBuyUI::dimandButtonEvent));
    addChild(baoshiBtn);
    baoshiBtn->setPosition(Point(dimandView->getPosition().x + dimandView->getSize().width/2 + 10 + baoshiBtn->getSize().width/2,
                                 dimandView->getPosition().y));
    
    //setup red star
    ImageView *starBkView = ImageView::create();
    starBkView->setScale9Enabled(true);
    starBkView->loadTexture("UI/dipang.png");
    starBkView->setSize(Size(s.width*0.45, 50));
    addChild(starBkView);
    starBkView->setPosition(Point(starBkView->getSize().width/2 + 20,
                                  baoshiBtn->getPosition().y - baoshiBtn->getSize().height/2 - starBkView->getSize().height/2 - 10));
    
    ImageView* star1 = ImageView::create();
    star1->loadTexture("UI/aixin.png");
    starBkView->addChild(star1);
    star1->setPosition(Point(-starBkView->getSize().width/2 + star1->getSize().width/2 + 5, -5));
    
    ImageView* star2 = ImageView::create();
    star2->loadTexture("UI/aixin.png");
    starBkView->addChild(star2);
    star2->setPosition(Point(star1->getPosition().x + star1->getSize().width + 2, -5));
    
    ImageView* star3 = ImageView::create();
    star3->loadTexture("UI/aixin.png");
    starBkView->addChild(star3);
    star3->setPosition(Point(star2->getPosition().x + star2->getSize().width + 2, -5));
    
    ImageView* star4 = ImageView::create();
    star4->loadTexture("UI/aixin.png");
    starBkView->addChild(star4);
    star4->setPosition(Point(star3->getPosition().x + star3->getSize().width + 2, -5));
    
    ImageView* star5 = ImageView::create();
    star5->loadTexture("UI/aixin.png");
    starBkView->addChild(star5);
    star5->setPosition(Point(star4->getPosition().x + star4->getSize().width + 2, -5));
    
    //设置
    Button* setupBtn = Button::create();
    setupBtn->setTouchEnabled(true);
    setupBtn->setScale9Enabled(true);
    setupBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    setupBtn->setSize(Size(s.width/10, s.width/12));
    setupBtn->addTouchEventListener(this, toucheventselector(PropBuyUI::setupButtonEvent));
    addChild(setupBtn);
    setupBtn->setPosition(Point(s.width - setupBtn->getSize().width/2 - 10, starBkView->getPosition().y));
    
    alert = gui::Text::create();
    alert->setText("设置");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    setupBtn->addChild(alert);
    
    //box
    
    Button* boxBtn = Button::create();
    boxBtn->setTouchEnabled(true);
    boxBtn->setScale9Enabled(true);
    boxBtn->loadTextures("UI/anniu_push.png", "UI/anniu_pop.png", "");
    boxBtn->setSize(Size(s.width/10, s.width/12));
    boxBtn->addTouchEventListener(this, toucheventselector(PropBuyUI::boxButtonEvent));
    addChild(boxBtn);
    boxBtn->setPosition(Point(setupBtn->getPosition().x - setupBtn->getSize().width - 10, starBkView->getPosition().y));
    
    alert = gui::Text::create();
    alert->setText("BOX");
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
    alert->setColor(Color3B::BLACK);
    boxBtn->addChild(alert);

}

void PropBuyUI::setupListView()
{
    auto layercolor = (LayerColor*)this->getChildByTag(0);
    
    auto backsize = layercolor->getContentSize();
    auto s = Director::getInstance()->getWinSize();
    
    // Create the list view ex
    ListView* listView = ListView::create();
    // set list view ex direction
    listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);
    listView->setBackGroundImage("UI/dipang.png");
    listView->setBackGroundImageScale9Enabled(true);
    listView->setSize(Size(backsize.width-10, backsize.height*0.95));
    listView->setPosition(Point((s.width - backsize.width) / 2.0f +
                                (backsize.width - listView->getSize().width) / 2.0f,
                                
                                (s.height - backsize.height) / 2.0f + 5 +
                                (backsize.height - listView->getSize().height) / 2.0f));
    
    listView->addEventListenerListView(this, listvieweventselector(PropBuyUI::selectedItemEvent));
    this->addChild(listView);
    
    ImageView* default_sprite = ImageView::create();
    default_sprite->loadTexture("UI/daojubiaoqian.png");

    Layout* default_item = Layout::create();
    default_item->setTouchEnabled(true);
    default_item->setSize(default_sprite->getContentSize());
    default_sprite->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
    default_item->addChild(default_sprite);
    
    // set model
    listView->setItemModel(default_item);
    
    const char* strdaoju[] = {
                              "UI/d_baibaoxiang.png",
        
                              "UI/d_20xiao_zhadan.png",
                              "UI/d_huanse.png",
                              "UI/d_sanxiao_zhadan.png",
        
                              "UI/d_shizi_zhadan.png",
                              "UI/d_tongse_zhadan.png",
                              "UI/d_zhadan.png"
    };
    
    colorSpriteEnum strcs[] = {
        
        kPropBaiXiang,        //宝箱
        
        kPropRandomBoom,      //随机炸弹
        kPropFivePlaces,      //5色刷新
        kPropAutoClear,       //自动胶囊
        
        kPropCorssBoomb,      //十字炸弹
        kPropSameColorBoomb,  //同色胶囊
        kPropBoomb,           //炸弹胶囊
    };
    
    int num[] = {0,0,0,0,
                 0,0,0,0,
                 0};
    
    static_propMap.clear();
    _csVector.clear();
    
    static_propMap.insert(std::pair<colorSpriteEnum, int>(kPropRandomBoom, 0));
    static_propMap.insert(std::pair<colorSpriteEnum, int>(kPropFivePlaces, 0));
    static_propMap.insert(std::pair<colorSpriteEnum, int>(kPropAutoClear,  0));
    static_propMap.insert(std::pair<colorSpriteEnum, int>(kPropCorssBoomb, 0));
    static_propMap.insert(std::pair<colorSpriteEnum, int>(kPropSameColorBoomb, 0));
    static_propMap.insert(std::pair<colorSpriteEnum, int>(kPropBoomb, 0));
    
    _csVector.push_back(kPropRandomBoom);
    _csVector.push_back(kPropFivePlaces);
    _csVector.push_back(kPropAutoClear);
    _csVector.push_back(kPropCorssBoomb);
    _csVector.push_back(kPropSameColorBoomb);
    _csVector.push_back(kPropBoomb);
    
    
    int size = sizeof strdaoju / sizeof strdaoju[0];
    // add custom item
    for (size_t i = 0; i < size; ++i)
    {
        ImageView* custom_sprite = ImageView::create();
        custom_sprite->loadTexture("UI/daojubiaoqian.png");
        
        Layout *custom_item = Layout::create();
        custom_item->setSize(custom_sprite->getContentSize());
        custom_sprite->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
        custom_item->addChild(custom_sprite);
        listView->pushBackCustomItem(custom_item);
        
        ImageView* prop = ImageView::create();
        prop->loadTexture(strdaoju[i]);
        prop->setPosition((Point(-custom_sprite->getSize().width/2 + prop->getSize().width, 0)));
        custom_sprite->addChild(prop);
        
        if(i!=0){
            int val = num[i-1];
            char buf[10];
            sprintf(buf, "%d", val);
            
            gui::Text* label = gui::Text::create();
            label->setText(buf);
            label->setFontName("AmericanTypewriter");
            label->setFontSize(30);
            label->setColor(Color3B::BLACK);
            prop->addChild(label);
            label->setPosition(Point(prop->getSize().width/2  - label->getSize().width/2,
                                     prop->getSize().height/2));
            
            _propLabelPrices.pushBack(label);
        }
        
        Button* custom_button = Button::create();
        custom_button->setName("Title Button");
        custom_button->setTouchEnabled(true);
        custom_button->loadTextures("UI/buy01.png", "UI/buy02.png", "");
        custom_button->setScale9Enabled(true);
        custom_button->setSize(Size(custom_button->getContentSize().width, custom_button->getContentSize().height));
        custom_button->setPosition(Point(custom_sprite->getSize().width/2 - custom_button->getSize().width/2, 0));
        custom_sprite->addChild(custom_button);
        custom_button->addTouchEventListener(this, toucheventselector(PropBuyUI::buyButtonEvent));
        custom_button->setTag(i);
        
        //道具价格 跟说明
        const char* name = "道具价格跟说明";
        gui::Text* label = gui::Text::create();
        label->setText(name);
        label->setFontName("AmericanTypewriter");
        label->setFontSize(30);
        custom_sprite->addChild(label);
    }
    
    //set all items layout gravity
    listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
    
    //set items margin
    listView->setItemsMargin(2.0f);
}

void PropBuyUI::petButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("pet button event");
}

void PropBuyUI::monsterButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("monster button event");
    
    float duration = 0.5f;
    auto layer = monsterAtlas::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void PropBuyUI::extractButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("extract button event");
}

void PropBuyUI::fightButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    CCLOG("fight button event");
    float duration = 0.5f;
    auto layer = match::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void PropBuyUI::buyButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    if(type == gui::TOUCH_EVENT_ENDED)
    {
        auto  btn = (Button*)pSender;
        int idx = btn->getTag();
        if(idx == 0)
        {
            processBuy(0);
        }
        else
        {
            const char* name = "购买成功";
            int fontsize = 30;
            auto s = Director::getInstance()->getWinSize();
            TTFConfig ttfConfig("fonts/wt021.ttf",fontsize,GlyphCollection::DYNAMIC, name);
            auto label = Label::createWithTTF(ttfConfig, name, TextHAlignment::CENTER, s.width);
            label->setAnchorPoint(Point::ANCHOR_MIDDLE);
            label->setPosition(Point(s.width/2,s.height/2));
            label->setLabelEffect(LabelEffect::GLOW,Color3B::YELLOW);
            this->addChild(label);
            
            auto action = Sequence::create(ScaleTo::create(0.5f,4.0f,4.0f),
                                           ScaleTo::create(0.5f,1.0f,1.0f),
                                           nullptr);
            label->runAction(Sequence::create(action,RemoveSelf::create(),nullptr));
            
            int index = idx-1;
            gui::Text* guilabel = _propLabelPrices.at(index);
            if(guilabel)
            {
                std::string strval = guilabel->getStringValue();
                int val = atoi(strval.c_str());
                char buf[10];
                val = val + 1;
                sprintf(buf, "%d", val);
                guilabel->setText(buf);
            }
            
            colorSpriteEnum cs = _csVector[index];
            int v = static_propMap[cs];
            static_propMap[cs] = v-1;
        }
    }
}

void PropBuyUI::coinButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
}

void PropBuyUI::dimandButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    
}

void PropBuyUI::setupButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    float duration = 0.5f;
    auto layer = setUI::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void PropBuyUI::boxButtonEvent(cocos2d::Object *pSender, TouchEventType type)
{
    float duration = 0.5f;
    auto layer = BOXUI::createScene();
    auto scene = TransitionFade::create(duration, layer, Color3B::WHITE);
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void PropBuyUI::selectedItemEvent(Object *pSender, ListViewEventType type)
{
    switch (type)
    {
        case LISTVIEW_ONSELECTEDITEM:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            int index = listView->getCurSelectedIndex();
            CCLOG("select child index = %d", index);
        }
            break;
            
        default:
            break;
    }
}

void PropBuyUI::processBuy(int index)
{
    /*游戏时间增加3秒
     游戏时间增加5秒
     清算消除方块积分1.5倍
     清算消除方块积分2倍
     完成后积分增加3%
     完成后积分增加5%
     完成后积分增加10%
     从上方落下特殊方块，点击后，以该元素为基础，消除十字元素方块
     从上方落下特殊方块，点击后，场景刷新为5种颜色区块
     从上方落下特殊方块，点击后，包括该方块在内，随机产生20个方块的爆炸 
    */
    
    CCLOG("index:%d\n", index);
    int num[] = {15,10,10,10,15,15,10,5,5,5};
    //抽取道具
    if(index == 0)
    {
        colorSpriteEnum cs;
        int val = computePropsProbability(num, sizeof num / sizeof num[0]);
        
        if(val == 0)
        {
            cs = kPropGameTimeAddThreeSec;
            showExtraction("游戏时间增加3秒");
        }
        
        else if(val == 1)
        {
            cs = kPropGameTimeAddFiveSec;
            showExtraction("游戏时间增加5秒");
        }
        else if(val == 2)
        {
            cs = kPropScoreDouble1Point5;
            showExtraction("清算消除方块积分1.5倍");
        }
        else if(val == 3)
        {
            cs = kPropScoreDouble2;
            showExtraction("清算消除方块积分2倍");
        }
        else if(val == 4)
        {
            cs = kPropScore3Percent;
            showExtraction("完成后积分增加3%");
        }
        else if(val == 5)
        {
            cs = kPropScore5Percent;
            showExtraction("完成后积分增加5%");
        }
        else if(val == 6)
        {
            cs = kPropScore10Percent;
            showExtraction("完成后积分增加10%");
        }
        else if(val == 7)
        {
            cs = kPropCorssBoomb;
            showExtraction("从上方落下特殊方块，点击后，以该元素为基础，消除十字元素方块");
        }
        else if(val == 8)
        {
            cs = kPropFivePlaces;
            showExtraction("从上方落下特殊方块，点击后，场景刷新为5种颜色区块");
        }
        else if(val == 9)
        {
            cs = kPropRandomBoom;
            showExtraction("从上方落下特殊方块，点击后，包括该方块在内，随机产生20个方块的爆炸");
        }
    }
}

void PropBuyUI::showExtraction(const char* tipword)
{
    int fontsize = 30;
    auto s = Director::getInstance()->getWinSize();
    // Adding "啊" letter at the end of string to make VS2012 happy, otherwise VS will generate errors
    // like "Error 3 error C2146: syntax error : missing ')' before identifier 'label'";
    TTFConfig ttfConfig("fonts/wt021.ttf",fontsize,GlyphCollection::DYNAMIC, tipword);
    auto label = Label::createWithTTF(ttfConfig, tipword, TextHAlignment::CENTER, s.width);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setPosition(Point(s.width/2,150));
    label->setLabelEffect(LabelEffect::GLOW,Color3B::YELLOW);
    this->addChild(label);
    
    auto action = Sequence::create(
                                   ScaleTo::create(0.5f,4.0f,4.0f),
                                   ScaleTo::create(0.5f,1.0f,1.0f),
                                   nullptr);
    label->runAction(Sequence::create(action,RemoveSelf::create(),nullptr));
    return;
}

int PropBuyUI::computePropsProbability(int array[], int size)
{
    int val = random_range(1,101);
    for(int i=0; i<size; i++)
    {
        int a = array[i];
        //CCLog("val :%d, a:%d, i:%d\n", val, a, i);
        if(val <= a)
        {
            //CCLog("props:val:%d, a:%d, i:%d\n", val, a, i);
            return i;
        }
        val -= a;
    }
    return 0;
}

