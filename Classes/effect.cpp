//
//  effect.cpp
//  Match
//
//  Created by 程小二 on 14-3-5.
//
//

#include "effect.h"

effect::effect() {}

effect::~effect() {}

effect* effect::create()
{
    effect* pret = new effect;
    pret->init();
    pret->autorelease();
    return pret;
}

bool effect::init()
{
    return true;
}

//void effect::boxDeadEffect(const std::vector<coord>& vecs,  std::vector<FiniteTimeAction*>& actions)
//{
//    std::vector<coord>::const_iterator it = vecs.begin();
//    for(int i=0; it != vecs.end(); ++it, ++i)
//    {
//        coord cd = *it;
//        int r = cd.r;
//        int c = cd.c;
//        
//        auto delay = DelayTime::create(i*0.2);
//        auto bind = CallFunc::create( std::bind(&effect::boxDead, this, r,c));
//        actions.push_back(delay);
//        actions.push_back(bind);
//    }
//}
//
//void effect::boxDead(int r, int c)
//{
//    _rc[r][c] = kUnSigned;
//    if(_rcSprites[r][c])
//    {
//        _rcSprites[r][c]->removeFromParentAndCleanup(true);
//        _rcSprites[r][c]=nullptr;
//    }
//     
//    auto emitter = ParticleSystemQuad::create("Particles/grapes_splurt.plist");
//    addChild(emitter);
//    Point pt = _batchnode->convertToWorldSpace(_boxesPos[r][c]);
//    emitter->setPosition(pt);
//    emitter->setScale(0.5f);
//    emitter->setDuration(0.01);
//    //play bomb sound*/
//}

void effect::crossBoomb(const std::vector<coord>& colVecs, const std::vector<coord>& rowVecs)
{
    /*
    std::vector<FiniteTimeAction*> colActions;
    std::vector<FiniteTimeAction*> rowActions;
    boxDeadEffect(colVecs, colActions);
    boxDeadEffect(rowVecs, rowActions);
    
    auto spawn = Spawn::create(colActions, rowActions, NULL);
    auto anim = CallFunc::create( std::bind(&effect::crossBoombAnimation, this));
    auto seq = Sequence::create(spawn,anim,NULL);
    this->runAction(seq);*/
}

void effect::crossBoombAnimation(Point pos)
{
    auto sprite = Sprite::create("animation/energy_ball01.png");
    this->addChild(sprite);
    sprite->setPosition(pos);
    
    Animation* animation = Animation::create();
    for(int i=1;i<4;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "animation/energy_ball%02d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.08);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    sprite->runAction(RepeatForever::create(action));
}







