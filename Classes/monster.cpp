//
//  monster.cpp
//  Match
//
//  Created by 程小二 on 14-2-15.
//
//

#include "monster.h"
#include "cocostudio/CocoStudio.h"
#include "gui/CocosGUI.h"
#include "util.h"

USING_NS_CC;
using namespace cocostudio;
using namespace gui;

monster::monster() :
_monster_pos(-1,-1)
{}

monster::~monster() {}

monster* monster::create()
{
    monster *pret = new monster;
    pret->autorelease();
    pret->init();
    return pret;
}

bool monster::init()
{
    setupMonster();
    return true;
}

void monster::hurt()
{
    auto sprite_monster = (Sprite*)getChildByTag(0);
    auto scaleto = ScaleTo::create(0.5f, 1.3);
    auto scaleto_back = ScaleTo::create(0.5f, 1.0f);
    sprite_monster->runAction(Sequence::create(scaleto, scaleto_back, NULL));
}

void monster::setupMonster()
{
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create("card/card_dog_face_1.png");
    addChild(sprite,0,kMonster);
    
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width/3);
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x01);
    body->setDynamic(false);
    sprite->setPhysicsBody(body);
    sprite->setPosition(Point(s.width*0.8,
                              s.height - sprite->getContentSize().height));
    _monster_pos = sprite->getPosition();
    
    //setup monster hp
    auto bkbar = Sprite::create("slidbar.png");
    bkbar->setColor(Color3B::GRAY);
    addChild(bkbar,0,kMonsterHp);
    bkbar->setPosition(Point(Point(_monster_pos.x, _monster_pos.y - sprite->getContentSize().height/2-5)));
    
    LoadingBar* monsterHpBar = LoadingBar::create();
    monsterHpBar->setTag(0);
    monsterHpBar->loadTexture("slidbar.png");
    monsterHpBar->setDirection(LoadingBarTypeLeft);
    monsterHpBar->setPercent(50);
    monsterHpBar->setPosition(Point(bkbar->getContentSize().width/2, bkbar->getContentSize().height/2));
    bkbar->addChild(monsterHpBar,0,0);
}

//today has little of been mad.!!!!!!!


