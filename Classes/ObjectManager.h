//
//  ObjectManager.h
//  PaoKu
//
//  Created by YTB on 13-11-27.
//
//

#ifndef __PaoKu__ObjectManager__
#define __PaoKu__ObjectManager__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class ObjectManager
{
private:
    //cpSpace *pSpace;
    CCSpriteBatchNode *pSpriteSheet;
    std::list<CCSprite *> objects;
	cpSpace* pSpace;
	b2World* pWorld;
public:
    //ObjectManager(CCSpriteBatchNode *spriteSheet, cpSpace *space);
	 ObjectManager(CCSpriteBatchNode *spriteSheet, b2World *world);
    ~ObjectManager();

    void initObjectOfMap(int mapIndex, float mapWidth);
    void removeObjectOfMap(int mapIndex);
    void remove(CCSprite *obj);

};

#endif /* defined(__PaoKu__ObjectManager__) */
