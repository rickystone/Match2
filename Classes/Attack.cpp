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
    auto sprite = Sprite::create("matchBox/s_tudou_b.png");
    sprite->setScale(0.25f);
    
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width/2);
    body->setCategoryBitmask(0x04);
    body->setCollisionBitmask(0x04);
    body->setGroup(10);
    body->setRotationEnable(true);
    sprite->setPhysicsBody(body);
    
    
    /*
    Point offset  = ccpSub(destination, startPoint);
    float   ratio = offset.y/offset.x;
    //calc rotation
    float rotationRadians = CC_DEGREES_TO_RADIANS(ratio);
    //vector for rotation
    Point directionVector = Point(sinf(rotationRadians), cosf(rotationRadians));
    
    Point force = ccpMult(directionVector, 5);
    body->applyImpulse(force);
    body->setVelocity(force);
    this->addChild(sprite);
    sprite->setPosition(startPoint);*/
    
    ccBezierConfig bezier;
    bezier.controlPoint_1 = startPoint;
    bezier.endPosition = destination;
    bezier.controlPoint_2 = Point(frandom_range(startPoint.x, destination.y), frandom_range(startPoint.y, destination.y));
    auto bezierTo = BezierTo::create(0.5, bezier);
    
    auto bind1  = CallFunc::create( std::bind(&Attack::stopBulletSpeed, this, sprite));
    auto s1 = Sequence::create(bezierTo, bind1, NULL);
    auto fadeout = FadeOut::create(1.0f);
    auto removeSelf = RemoveSelf::create();
    auto seq = Sequence::create(s1,DelayTime::create(0.2f),fadeout,removeSelf,NULL);
    sprite->runAction(seq);
    this->addChild(sprite);
    sprite->setPosition(startPoint);
}

void Attack::stopBulletSpeed(Sprite* bullet)
{
    //bullet->getPhysicsBody()->setVelocity(Vect(0,0));
    ///auto rotate = RotateBy::create(1.5, 360);
}
