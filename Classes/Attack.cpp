//
//  Attack.cpp
//  Match
//
//  Created by 程小二 on 14-2-16.
//
//

#include "Attack.h"
#include "util.h"

Attack::Attack() {}

Attack::~Attack() {}

bool Attack::init()
{
    return true;
}

Attack* Attack::create()
{
    Attack* pret = new Attack;
    pret->autorelease();
    pret->init();
    return pret;
}

void Attack::shootBullet(int r, int c, Point destination, Point startPoint)
{
    auto sprite = Sprite::createWithSpriteFrameName("zidan.png");
    
    /*auto sprite = Sprite::create("animation/energy_ball01.png");
    Animation* animation = Animation::create();
    for(int i=1;i<=4;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "animation/energy_ball%02d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.08);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    sprite->runAction(RepeatForever::create(action));*/
    
    
    float speed = 250;
    float distance = startPoint.getDistance(destination);
    float duration = distance/speed;
    
    /*ccBezierConfig bezier;
    bezier.controlPoint_1 = startPoint;
    bezier.endPosition = destination;
    bezier.controlPoint_2 = Point(frandom_range(startPoint.x, destination.y), frandom_range(startPoint.y, destination.y));
    auto bezierTo = BezierTo::create(duration, bezier);*/
    
    sprite->setScale(0.01f);
    auto scaleto = ScaleTo::create(BOXSCALEDURATION, 1.0f);
    auto moveto = MoveTo::create(duration, destination);
    
    auto rotate = RotateBy::create(5.0, 360);
    sprite->runAction(RepeatForever::create(rotate));
    
    auto call = CallFunc::create( CC_CALLBACK_0(Attack::callback2,this,sprite));
    
    auto seq = Sequence::create(scaleto,moveto, call, RemoveSelf::create(), NULL);
    sprite->runAction(seq);
    this->addChild(sprite);
    sprite->setPosition(startPoint);
}

void Attack::killMe()
{
    CCLOG("attack kill me");
}

void Attack::callback2(Node* sender)
{
    Sprite* xx = (Sprite*)sender;
    Point pt = xx->getPosition();
    
    Sprite* sprite = Sprite::createWithSpriteFrameName("zidan.png");
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width/2);
    body->setCategoryBitmask(0x04);
    body->setCollisionBitmask(0x04);
    body->setGroup(10);
    sprite->setPhysicsBody(body);
    sprite->setPosition(pt);
    sprite->setRotation(xx->getRotation());
    addChild(sprite,0,10);
    
    auto seq = Sequence::create(DelayTime::create(0.5f), CallFunc::create( std::bind(&Attack::fuckxx, this, sprite)),
                                DelayTime::create(1.0f),
                                RemoveSelf::create(),
                                NULL);
    this->runAction(seq);
}


void Attack::fuckxx(Sprite* xx)
{
    PhysicsBody* body = xx->getPhysicsBody();
    body->removeFromWorld();
    
    auto rotate = RotateBy::create(4.0, 360);
    auto repeat = RepeatForever::create(rotate);
    
    auto moveby = MoveBy::create(1.0f, Point(0,-30));
    
    xx->runAction(repeat);
    xx->runAction(moveby);

}


