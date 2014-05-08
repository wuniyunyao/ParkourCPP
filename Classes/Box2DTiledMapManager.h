#pragma once
#include "Box2DTMXReader.h"
#include "Coin.h"
#include "Monster.h"
/*
�ļ�����Box2DTiledMapManager.h
�������ù������ڽ����������Box2DTMXReader�����ĵ�ͼ�����������Զ��ͷ�
�����ߣ�������ң
�������ڣ�2013/4/24
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
	bool readTiledMapForMonsters(CCSpriteBatchNode* spritesheet,b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMapForMonsters(CCSpriteBatchNode* spritesheet,b2World* world,CCTMXTiledMap *tiledmap);
	void destroyBody(b2Body* body);
private:
	std::list<Box2DTMXReader*> blockReaderList;	
	std::list<Box2DTMXReader*> coinReaderList;	
	std::list<Box2DTMXReader*> monsterReaderList;	
	bool autorelease();
	inline void bindSpriteForCoins(CCSpriteBatchNode* spritesheet,b2Body* body);
	inline void bindSpriteForMonsters(CCSpriteBatchNode* spritesheet,b2Body* body);
	CC_SYNTHESIZE(int, blockReaderListLength,BlockReaderListLength);
	CC_SYNTHESIZE(int, coinReaderListLength,CoinReaderListLength);
	CC_SYNTHESIZE(int, monsterReaderListLength,MonsterReaderListLength);
	b2World* mWorld;
};

