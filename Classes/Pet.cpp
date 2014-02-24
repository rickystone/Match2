//
//  Pet.cpp
//  Match
//
//  Created by 程小二 on 14-2-17.
//
//

#include "Pet.h"
#include "util.h"

Pet::Pet() {}

Pet::~Pet() {}

Pet* Pet::create()
{
    Pet *pret = new Pet;
    pret->init();
    pret->autorelease();
    return pret;
}

bool Pet::init()
{
    setupPet();
    return true;
}

void Pet::setupPet()
{
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create("card/card_dog_face_2.png");
    addChild(sprite,0,kPet);
    sprite->setPosition(Point(sprite->getContentSize().width + 60,
                              s.height - sprite->getContentSize().height));
}

void Pet::removePet()
{
    this->removeChildByTag(kPet);
}
