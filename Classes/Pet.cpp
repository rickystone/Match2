//
//  Pet.cpp
//  Match
//
//  Created by 程小二 on 14-2-17.
//
//

#include "Pet.h"
#include "util.h"


#include "cocostudio/CocoStudio.h"

using namespace cocostudio;

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
    
    //remove sigle resource
    ArmatureDataManager::getInstance()->removeArmatureFileInfo("Export/dongzuo.ExportJson");
    //load resource directly
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/dongzuo.ExportJson");
    Armature *armature = Armature::create("dongzuo");
    armature->getAnimation()->playWithIndex(0);
    addChild(armature);
    armature->setPosition(Point(armature->getContentSize().width,
                              s.height - armature->getContentSize().height-50));
}

void Pet::removePet()
{
    this->removeChildByTag(kPet);
}
