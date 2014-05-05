//
//  PlayScene.cpp
//  Parkour
//
//  Created by YTB on 13-11-20.
//
//

#include "PlayScene.h"
#include "StatusLayer.h"
#include "GameOverLayer.h"
#include "Runner.h"
#include "MapManager.h"
#include "Constant.h"
#include "ObjectManager.h"
#include "SimpleAudioEngine.h"
#include "SimpleRecognizer.h"
#include "Resources.h"


#define NOTIFI_MEET_COIN "notification_meet_coin"
#define NOTIFI_MEET_ROCK "notification_meet_rock"

// c function for chipmunk
static void postStepRemove(cpSpace *space, cpShape *shape, void *param)
{
    /*ObjectManager *objectManager = (ObjectManager *)param;
    switch (shape->collision_type) {
        case SpriteTagcoin:
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFI_MEET_COIN);
            objectManager->remove((CCSprite *)shape->data);
            break;
        case SpriteTagrock:
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFI_MEET_ROCK);
            break;
        default:
            break;
    }*/
}

static int collisionBegin(cpArbiter *arb, cpSpace *space, void *param)
{
    /*// we get shapes here, so postStepRemove's second param is cpShape
    CP_ARBITER_GET_SHAPES(arb, a, b);
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)postStepRemove, b, param);
    return 0;*/
}

PlayLayer::PlayLayer():
lastEyeX(0)
{
}
CCScene* PlayLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    PlayLayer *playLayer = PlayLayer::create();
    playLayer->setTag(TAG_PLAYER);
    scene->addChild(playLayer);
    
    StatusLayer *statusLayer = StatusLayer::create();
    statusLayer->setTag(TAG_STATUSLAYER);
    scene->addChild(statusLayer);
    return scene;
}

PlayLayer::~PlayLayer()
{
    /*delete this->mapManager;
    delete this->objectManager;
    cpShapeFree(this->wallBottom);
    cpSpaceFree(this->space);*/
}

bool PlayLayer::init()
{
	//////////////////////////////////
	//new code for Box2D added by wuniyunyao
	if (!CCLayer::init()) {
        return false;
    }
	 setTouchEnabled(true);
	 setTouchMode(kCCTouchesOneByOne);
	 recognizer = new SimpleRecognizer();
	// initPhysics, must init first
	this->mWorld = new b2World(b2Vec2(0,-10));
	this->mWorld->SetAllowSleeping(true);
    this->mWorld->SetContinuousPhysics(true);
	this->mWorld->SetContactListener(this);

	b2Body* ground = NULL;
    b2BodyDef bd;
    ground = mWorld->CreateBody(&bd);

	// 地板
    b2EdgeShape shape;
    shape.Set(b2Vec2(0, MapManager::getGroundHeight() / PTM_RATIO), b2Vec2(INT_MAX, MapManager::getGroundHeight() /  PTM_RATIO));
	b2FixtureDef fixDef;
    fixDef.shape = &shape;
	fixDef.friction = 0;

    ground->CreateFixture(&fixDef);
	

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(SPRITESHEET);
    this->spriteSheet = CCSpriteBatchNode::create(SPRITEPACKER);
    this->addChild(spriteSheet,1);
	
	this->mapManager = new MapManager(this->spriteSheet,this, this->mWorld);

	this->runner = Runner::create(this->mWorld);
    this->spriteSheet->addChild(this->runner);

	//this->objectManager = new ObjectManager(this->spriteSheet, this->mWorld);
    //this->objectManager->initObjectOfMap(1, this->mapManager->getMapWidth());


	 scheduleUpdate();
	 setDebug(false);
	/////////////////////////////////
	/*
    // must after objectManager inited
    // make updater() to be called
    scheduleUpdate();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PlayLayer::notifiCoin),
                                                                  NOTIFI_MEET_COIN, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PlayLayer::notifiRock),
                                                                  NOTIFI_MEET_ROCK, NULL);
    
	*/
    return true;
}

bool PlayLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("PlayScene::ccTouchBegan");
    CCPoint pos = pTouch->getLocation();
    recognizer->beginPoint(pos.x, pos.y);
    return true;
}

void PlayLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pos = pTouch->getLocation();
    recognizer->movePoint(pos.x, pos.y);
}

void PlayLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("PlayScene::ccTouchEnded");
    
    SimpleGestures rtn = recognizer->endPoint();
    
    switch (rtn) {
        case SimpleGesturesUp:
        CCLOG("Runner::jump");
        this->runner->jump();
        break;
        
        case SimpleGesturesDown:
        CCLOG("Runner::crouch");
        this->runner->crouch();
        break;
        
        case SimpleGesturesNotSupport:
        case SimpleGesturesError:
        // try dollar Recognizer
        // 0:Use Golden Section Search (original)
        // 1:Use Protractor (faster)
        CCLOG("not support or error touch,use geometricRecognizer!!");
        break;
        
        default:
        break;
    }
}

void PlayLayer::onExit()
{
    /*CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFI_MEET_COIN);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFI_MEET_ROCK);*/
    
    CCLayer::onExit();
}

void PlayLayer::notifiCoin(CCObject *unuse)
{
    /*CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    audioEngine->playEffect("pickup_coin.mp3");
    StatusLayer *statusLayer = (StatusLayer *)getParent()->getChildByTag(TAG_STATUSLAYER);
    statusLayer->addCoin(1);*/
}

void PlayLayer::notifiRock(CCObject *unuse)
{
    /*GameOverLayer *gameoverLayer = GameOverLayer::create(ccc4(0, 0, 0, 180));
    gameoverLayer->setTag(TAG_GAMEOVER);
    getParent()->addChild(gameoverLayer);
    
    CCDirector::sharedDirector()->pause();*/
}

void PlayLayer::update(float dt)
{
 
    StatusLayer *statusLayer = (StatusLayer *)getParent()->getChildByTag(TAG_STATUSLAYER);
    statusLayer->updateMeter(lastEyeX);
	////////////////////////////////////////
	mWorld->Step(dt, 10, 8);
	this->pickCoins();
	if (true == this->mapManager->checkAndReload(this->lastEyeX)) {
      
    }
	
	lastEyeX = this->runner->getPositionX() - this->runner->getoffsetPx();
    CCCamera *camera = this->getCamera();
    float eyeZ = camera->getZEye();
    camera->setEyeXYZ(lastEyeX, 0, eyeZ);
    camera->setCenterXYZ(lastEyeX, 0, 0);

	this->runner->step(dt);
}

void PlayLayer::setDebug(bool isDebug)
{
    if (isDebug) {
        mDebugDraw = new GLESDebugDraw(PTM_RATIO);
        mWorld->SetDebugDraw(mDebugDraw);
        
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_pairBit;
        flags += b2Draw::e_centerOfMassBit;
        mDebugDraw->SetFlags(flags);
        draw();
        
    }
}

void PlayLayer::draw()
{
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    mWorld->DrawDebugData();
    
    kmGLPopMatrix();
}

void PlayLayer::BeginContact(b2Contact* contact)
{
	//    CCLog("begin contact!");
    
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    
    if (bodyUserDataA && bodyUserDataB)
    {
        CCPhysicsSprite* contactA = static_cast<CCPhysicsSprite*>(bodyUserDataA);
        CCPhysicsSprite* obj = NULL;
        if (contactA == this->runner)
        {
            obj = static_cast<CCPhysicsSprite*>(bodyUserDataB);
        }else
        {
            obj = static_cast<CCPhysicsSprite*>(bodyUserDataA);
        }
        
        if (COINTAG == obj->getTag()) {
           ((StatusLayer*)(this->getParent()->getChildByTag(TAG_STATUSLAYER)))->addCoin(1);
			mRemoveObjs.push_back(obj);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(PICKUPCOINS);
        }else if(ROCKTAG == obj->getTag())
        {
           /* mRunner->die();
            unscheduleUpdate();
            mState = GameOverState;
            GameOver* over = GameOver::create();
            this->getParent()->addChild(over);*/
        }
        
    }
}

void PlayLayer::pickCoins()
{
    if(!mRemoveObjs.empty())
	{
		std::vector<CCPhysicsSprite*>::iterator it;
		for(it=mRemoveObjs.begin();it!=mRemoveObjs.end();it++)
		{
			(*it)->setVisible(false);
		}
		mRemoveObjs.clear();
	}
}