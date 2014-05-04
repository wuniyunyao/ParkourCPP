//
//  Coin.h
//  PaoKu
//
//  Created by YTB on 13-11-25.
//
//

#ifndef __PaoKu__Coin__
#define __PaoKu__Coin__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D\Box2D.h"
#include "Box2DTiledMapManager.h"
USING_NS_CC;

class Coin : public extension::CCPhysicsSprite
{
public:
    static Coin *create(CCSpriteBatchNode *spriteSheet, b2Body *body);
    Coin(CCSpriteBatchNode *spriteSheet, b2Body *body);
    virtual void removeFromParent();
    
    
    static const CCSize* getCoinContentSize()
	{
        CCPhysicsSprite *sprite = CCPhysicsSprite::createWithSpriteFrameName("coin0.png");
        return &sprite->getContentSize();
	}
private:
    //cpSpace *pSpace;//weak ref
    //b2Shape *pShape;
    b2Body *pBody;

};

#endif /* defined(__PaoKu__Coin__) */
