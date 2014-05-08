//
//  Monster.h
//  PaoKu
//
//  Created by YTB on 13-11-26.
//
//

#ifndef __PaoKu__Monster__
#define __PaoKu__Monster__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D\Box2D.h"
#include "Box2DTiledMapManager.h"

USING_NS_CC;

class Monster : public extension::CCPhysicsSprite
{
public:
    static Monster *create(CCSpriteBatchNode *spriteSheet, b2Body *body);
    Monster(CCSpriteBatchNode *spriteSheet, b2Body *body);
    virtual void removeFromParent();
    
    static  const CCSize* getMonsterContentSize()
    {
        CCPhysicsSprite *sprite = CCPhysicsSprite::createWithSpriteFrameName("rock.png");
        return &sprite->getContentSize();

    };
private:
     b2Body *pBody;
};

#endif /* defined(__PaoKu__Monster__) */
