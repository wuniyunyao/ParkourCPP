//
//  Map.cpp
//  PaoKu
//
//  Created by YTB on 13-11-26.
//
//

#include "Monster.h"
#include "Map.h"
#include "Runner.h"
#include "Constant.h"
#include "MapManager.h"

#define GROUND_TAG (10)
#define MAP_TAG (11)

Map *Map::create(int index)
{
    Map *map = new Map(index);
    map->autorelease();
    return map;
}

Map::Map(int index)
{
    this->map=CCTMXTiledMap::create(getMapName(index));
	//this->setAnchorPoint(ccp(0, 0));
    this->map->setPosition(ccp(this->map->getContentSize().width * index, 0));
	this->map->setTag(MAP_TAG);
	//this->map->retain();
	this->addChild(this->map,0);
    
    CCSprite *ground = CCSprite::create(getGroundName(index));
    ground->setAnchorPoint(ccp(0, 1));
    ground->setTag(GROUND_TAG);
    ground->setPosition(ccp(this->map->getContentSize().width * index, MapManager::getGroundHeight()));
    this->addChild(ground,1);
}

Map::~Map()
{
}

const char *Map::getMapName(int index)
{
    CCString *fileName = CCString::createWithFormat( "map%02d.tmx", index % MAP_COUNT);
    return fileName->getCString();
}

const char *Map::getGroundName(int index)
{
    CCString *fileName = CCString::createWithFormat( "Ground%02d.png", index % MAP_COUNT);
    return fileName->getCString();
}

void Map::reload(int index)
{
	this->removeChildByTag(MAP_TAG);
	this->map=CCTMXTiledMap::create(getMapName(index));
    this->map->setPositionX(this->map->getContentSize().width * index);
	this->map->setTag(MAP_TAG);
	this->addChild(this->map,0);
	
    
    CCTexture2D *textureGround = CCTextureCache::sharedTextureCache()->addImage(getGroundName(index));
    CCSprite *ground = (CCSprite *)(this->getChildByTag(GROUND_TAG));
	ground->setPositionX(this->map->getContentSize().width * index);
    ground->setTexture(textureGround);
}

