//
//  MapManager.cpp
//  PaoKu
//
//  Created by YTB on 13-11-24.
//
//

#include "MapManager.h"
#include "Map.h"
#include "Constant.h"

MapManager::MapManager(CCLayer *parent, cpSpace *pSpace):
spriteWidth(0),
curMap(0)
{/*
    this->space = pSpace;

    this->map0 = Map::create(0);
    parent->addChild(this->map0);

    spriteWidth = this->map0->getContentSize().width;

    this->map1 = Map::create(1);
    parent->addChild(this->map1);*/
}
MapManager::MapManager(CCSpriteBatchNode* spritesheet,CCLayer *parent, b2World* mWorld):
spriteWidth(0),
curMap(0)
{
    this->mWorld = mWorld;
	this->mSpritesheet = spritesheet;

    this->map0 = Map::create(0);
    //parent->addChild(this->map0,0);
	tool.readTiledMapForBlocks(mWorld,this->map0->map);
	tool.readTiledMapForCoins(mSpritesheet, mWorld,this->map0->map);

    spriteWidth = this->map0->map->getContentSize().width;

    this->map1 = Map::create(1);
    //parent->addChild(this->map1,0);
	tool.readTiledMapForBlocks(mWorld,this->map1->map,spriteWidth);
	tool.readTiledMapForCoins(mSpritesheet, mWorld,this->map1->map,spriteWidth);
}

MapManager::~MapManager()
{
}

bool MapManager::checkAndReload(float eyeX)
{
    int newCur = eyeX / spriteWidth;
    if (curMap == newCur) {
        return false;
    }

    Map *currentMap = NULL;

    if (0 == newCur %2) {
        // change mapSecond
        currentMap = this->map1;
    } else {
        // change mapFirst
        currentMap = this->map0;
    }

    curMap = newCur;
    CCLOG("==load map:%d",(newCur + 1));
    currentMap->reload(curMap + 1);
	tool.readTiledMapForBlocks(mWorld,currentMap->map,spriteWidth*(curMap + 1));
    return true;
}