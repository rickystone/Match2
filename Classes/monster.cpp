//
//  monster.cpp
//  Match
//
//  Created by 程小二 on 14-2-15.
//
//

#include "monster.h"
#include "util.h"

USING_NS_CC;
using namespace gui;

monster::monster() :
_monster_pos(-1,-1),
_pMonsterArmature(nullptr)
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
    CCLOG("monster hurt");
    auto monster = (Sprite*)getChildByTag(0);
    monster->stopAllActions();
    monster->setScale(1.0f);
    
    auto scaleto = ScaleTo::create(0.2f, 1.3);
    auto scaleto_back = ScaleTo::create(0.2f, 1.0f);
    monster->runAction(Sequence::create(scaleto, scaleto_back, NULL));
}

void monster::setupMonster()
{
    auto s = Director::getInstance()->getWinSize();
    //remove sigle resource
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("Export/dongzuo.ExportJson");
    //load resource directly
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/dongzuo.ExportJson");
    _pMonsterArmature = Armature::create("dongzuo");
    _pMonsterArmature->getAnimation()->playWithIndex(0);
    addChild(_pMonsterArmature,0,0);
    _pMonsterArmature->setPosition(Point(_pMonsterArmature->getContentSize().width,
                                s.height - _pMonsterArmature->getContentSize().height-50));
    
    _pMonsterArmature->setPosition(Point(s.width*0.8,
                              s.height - _pMonsterArmature->getContentSize().height-50));
    _monster_pos = _pMonsterArmature->getPosition();
    

    auto body = PhysicsBody::createCircle(_pMonsterArmature->getContentSize().width/3);
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x01);
    body->setDynamic(false);
    _pMonsterArmature->setPhysicsBody(body);

    //setup monster hp
    auto bkbar = Sprite::create("slidbar.png");
    bkbar->setColor(Color3B::GRAY);
    addChild(bkbar,0,kMonsterHp);
    bkbar->setPosition(Point(Point(_monster_pos.x, _monster_pos.y - _pMonsterArmature->getContentSize().height/2-5)));
    
    LoadingBar* monsterHpBar = LoadingBar::create();
    monsterHpBar->setTag(0);
    monsterHpBar->loadTexture("slidbar.png");
    monsterHpBar->setDirection(LoadingBarTypeLeft);
    monsterHpBar->setPercent(50);
    monsterHpBar->setPosition(Point(bkbar->getContentSize().width/2, bkbar->getContentSize().height/2));
    bkbar->addChild(monsterHpBar,0,0);
}

