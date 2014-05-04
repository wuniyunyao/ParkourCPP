#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class Box2DObjectManager
{
/*private:
	CCSpriteBatchNode *pSpriteSheet;
    std::list<CCSprite *> objects;
	b2World* pWorld;
	CCTMXTiledMap* mTiledmap;*/
public:
	Box2DObjectManager(void);
	virtual ~Box2DObjectManager(void);
	/*void initObjectOfMap(int mapIndex, float mapWidth);
    void removeObjectOfMap(int mapIndex);
    void remove(CCSprite *obj);*/
};

