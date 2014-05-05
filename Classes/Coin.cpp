//
//  Coin.cpp
//  PaoKu
//
//  Created by YTB on 13-11-25.
//
//

#include "Coin.h"
#include "Constant.h"
#include "Resources.h"
Coin *Coin::create(CCSpriteBatchNode *spriteSheet, b2Body *body)
{
    Coin *coin = new Coin(spriteSheet,body);
    coin->autorelease();
    return coin;
}

Coin::Coin(CCSpriteBatchNode *spriteSheet, b2Body *body)
{
	this->pBody = body;

    CCArray *animFrames = CCArray::create();
    for (int i = 0; i < 8; i++)
    {
        CCString *name = CCString::createWithFormat("coin%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    CCAction *action =CCRepeatForever::create(CCAnimate::create(animation));

    this->initWithSpriteFrameName("coin0.png");

    // init physics
	this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);
    //float radius = 0.95 * this->getContentSize().width / 2;
    //this->pBody = cpBodyNewStatic();
    //cpBodySetPos(this->pBody, cpv(position.x, position.y));
    //this->setCPBody(this->pBody);

    //this->pShape = cpCircleShapeNew(this->pBody, radius, cpvzero);
    //this->pShape->collision_type = SpriteTagcoin;
    //this->pShape->sensor = true;
    //cpSpaceAddStaticShape(this->pSpace, this->pShape);

    // for collision
    body->SetUserData(this);
    this->setTag(COINTAG);
    this->runAction(action);
    spriteSheet->addChild(this);
}

void Coin::removeFromParent()
{
	pBody->GetWorld()->DestroyBody(pBody);
    CCPhysicsSprite::removeFromParent();
}