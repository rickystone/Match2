//
//  PropUI.cpp
//  Match
//
//  Created by 程小二 on 14-2-26.
//
//

#include "PropUI.h"

PropUI::PropUI() {}

PropUI::~PropUI() {}

PropUI* PropUI::create()
{
    PropUI* pret = new PropUI;
    pret->autorelease();
    pret->init();
    return pret;
}

bool PropUI::init()
{
    return true;
}


