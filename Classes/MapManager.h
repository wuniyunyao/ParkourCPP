//
//  MapManager.h
//  PaoKu
//
//  Created by YTB on 13-11-24.
//
//

#ifndef __PaoKu__MapManager__
#define __PaoKu__MapManager__

#include "cocos2d.h"
#include "chipmunk.h"
#include "Box2D\Box2D.h"
#include "Box2DTiledMapManager.h"

USING_NS_CC;

class Map;

class MapManager
{
private:

    float spriteWidth;
    int curMap;// being displayed
    
    Map *map0;
    Map *map1;
	///////////////////////
	b2World* mWorld;
	Box2DTiledMapManager tool;
	CCSpriteBatchNode* mSpritesheet;
public:
	MapManager(CCSpriteBatchNode* spritesheet, CCLayer *parent, b2World *mWorld);
    ~MapManager();

    static float getGroundHeight() {return 50.0;};

    float getMapWidth() {return spriteWidth;};
    int getCurMap() {return curMap;};

    bool checkAndReload(float eyeX);
};

#endif /* defined(__PaoKu__MapManager__) */
