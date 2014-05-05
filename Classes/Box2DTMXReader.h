#ifndef __BOX2DTMXTOOL_H_
#define __BOX2DTMXTOOL_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D\Box2D.h"
#include "StaticBlockObject.h"
#include "Coin.h"

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif
using namespace cocos2d;
/*
�ļ�����Box2DTMLTool.h
�������ù������ڽ�tiled map�еĵ��ζ�����Box2Dʹ��
�����ߣ�������ң
�������ڣ�2013/4/24
*/
class Box2DTMXReader{
public:
	Box2DTMXReader();
	~Box2DTMXReader();
	bool readTiledMap(b2World* world,CCTMXTiledMap *tiledmap,float xOffset,const char* layerName,b2BodyType type);
	bool readTiledMapForMultipleBodys(b2World* world,CCTMXTiledMap *tiledmap,float xOffset,const char* layerName,b2BodyType type);
	bool readTiledMap(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMapForMultipleBodys(b2World* world,CCTMXTiledMap *tiledmap,float xOffset);
	bool readTiledMap(b2World* world,CCTMXTiledMap *tiledmap);
	bool readTiledMapForMultipleBodys(b2World* world,CCTMXTiledMap *tiledmap);

	void destory();
	std::vector<IdentifiedObject*> mIdentifiedObjectList;
	/*b2Body* getBody(){
		return mBody;
	};*/
private:
	enum flag{
		single,
		multiple
	};
	flag mode;
	CCTMXTiledMap* mTiledMap;
	b2Body* mBody;	
	float contentScaleFactor;
	float curXOffset;
	b2World* mWorld;
	CC_SYNTHESIZE(int, bodyListLength,BodyListLength);
	//std::list<b2Body*> mBlocksBodyList;
	//bool autorelease();
};
#endif //__BOX2DTMXTOOL_H_