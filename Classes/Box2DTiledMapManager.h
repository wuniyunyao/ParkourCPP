#pragma once
#include "Box2DTMXReader.h"
#include "Coin.h"
/*
文件名：Box2DTiledMapManager.h
描述：该工具用于将处理多张由Box2DTMXReader读出的地图，并管理其自动释放
创建者：无逆云遥
创建日期：2013/4/24
*/
using namespace extension;
using namespace cocos2d;
class Box2DTiledMapManager
{
public:
	Box2DTiledMapManager(void);
	~Box2DTiledMapManager(void);
	bool readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap);
	bool readTiledMapForCoins(CCSpriteBatchNode* spritesheet,b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMapForCoins(CCSpriteBatchNode* spritesheet,b2World* world,CCTMXTiledMap *tiledmap);
	void destroyBody(b2Body* body);
private:
	std::list<Box2DTMXReader*> blockReaderList;	
	std::list<Box2DTMXReader*> coinReaderList;	
	bool autorelease();
	inline void bindSprite(CCSpriteBatchNode* spritesheet,b2Body* body);
	CC_SYNTHESIZE(int, blockReaderListLength,BlockReaderListLength);
	CC_SYNTHESIZE(int, coinReaderListLength,coinReaderListLength);
	b2World* mWorld;
};

