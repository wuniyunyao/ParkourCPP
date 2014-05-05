//
//  PlayScene.h
//  Parkour
//
//  Created by YTB on 13-11-20.
//
//

#ifndef __Parkour__PlayScene__
#define __Parkour__PlayScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif


USING_NS_CC;
USING_NS_CC_EXT;


class Runner;
class MapManager;
class ObjectManager;
class SimpleRecognizer;

enum {
    TAG_STATUSLAYER = 10,
    TAG_GAMEOVER,
    TAG_PLAYER,
};

class PlayLayer : public CCLayer ,public b2ContactListener
{
public:
    CREATE_FUNC(PlayLayer);
	PlayLayer();
    ~PlayLayer();
    virtual void onExit();
    virtual bool init();
    virtual void update(float dt);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    static CCScene* scene();

private:
	b2World* mWorld;
    CCSpriteBatchNode *spriteSheet;
    Runner *runner;
    MapManager *mapManager;
    ObjectManager *objectManager;
    float lastEyeX;
    
    void notifiCoin(CCObject *unuse);
    void notifiRock(CCObject *unuse);
    
    CCPoint touchBeganPoint,touchEndedPoint;
    std::list<CCPoint> points;
    
    SimpleRecognizer *recognizer;
	
	//Debug
	GLESDebugDraw* mDebugDraw; 
	// 绘制物理世界debug区域
    void draw();
    // 开启物理世界debug
    void setDebug(bool isDebug);
	virtual void BeginContact(b2Contact* contact);
	std::vector<extension::CCPhysicsSprite*> mRemoveObjs;
	void pickCoins();
};
#endif /* defined(__Parkour__PlayScene__) */
