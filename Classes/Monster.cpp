//
//  Monster.cpp
//  PaoKu
//
//  Created by YTB on 13-11-26.
//
//

#include "Monster.h"
#include "Map.h"
#include "MapManager.h"
#include "Runner.h"
#include "Constant.h"


Monster *Monster::create(CCSpriteBatchNode *spriteSheet, b2Body *body)
{
    Monster *rock = new Monster(spriteSheet,body);
    rock->autorelease();
    return rock;
}

Monster::Monster(CCSpriteBatchNode *spriteSheet, b2Body *body)
{
    this->pBody = body;
    
    //if ( position.y >= (MapManager::getGroundHeight() + Runner::getCrouchContentSize()->height) ) {
     //   this->initWithSpriteFrameName("hathpace.png");
    //} else {
        this->initWithSpriteFrameName("rock.png");
   // }

    // init physics
    this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);

    // for collision
    body->SetUserData(this);
	this->setTag(SpriteTagmonster);
    spriteSheet->addChild(this);
}

void Monster::removeFromParent()
{
    pBody->GetWorld()->DestroyBody(pBody);
    CCPhysicsSprite::removeFromParent();
}