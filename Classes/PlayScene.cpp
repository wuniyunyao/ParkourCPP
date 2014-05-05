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
    
    //StatusLayer *statusLayer = StatusLayer::create();
    //statusLayer->setTag(TAG_STATUSLAYER);
    //scene->addChild(statusLayer);
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
    
	/*if (!CCLayer::init()) {
        return false;
    }
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    recognizer = new SimpleRecognizer();
    
    // initPhysics, must init first
    this->space = cpSpaceNew();
    this->space->gravity = cpv(0, -350);
    wallBottom = cpSegmentShapeNew(this->space->staticBody,
                                   cpv(0, MapManager::getGroundHeight()),// start point
                                   cpv(4294967295, MapManager::getGroundHeight()),// MAX INT:4294967295
                                   0);// thickness of wall
    cpSpaceAddStaticShape(this->space, wallBottom);*/
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

	b2Body* ground = NULL;
    b2BodyDef bd;
    ground = mWorld->CreateBody(&bd);

	// 地板
    b2EdgeShape shape;
    shape.Set(b2Vec2(0, MapManager::getGroundHeight() / PTM_RATIO), b2Vec2(INT_MAX, MapManager::getGroundHeight() /  PTM_RATIO));
	b2FixtureDef fixDef;
    fixDef.shape = &shape;
	fixDef.friction = 0;
	//fixDef.restitution = -1;
    ground->CreateFixture(&fixDef);
	setDebug(false);

	

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("parkour.plist");
    this->spriteSheet = CCSpriteBatchNode::create("parkour.png");
    this->addChild(spriteSheet,1);
	/*//////////////////////////////////////////////////////////////////
	CCSprite* sprite;
	CCArray *animFrames = CCArray::create();
    for (int i = 0; i < 8; i++)
    {
        CCString *name = CCString::createWithFormat("coin%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    CCAction *action =CCRepeatForever::create(CCAnimate::create(animation));

    sprite->initWithSpriteFrameName("coin0.png");

    //body->SetUserData(this);
    
    sprite->runAction(action);
    spriteSheet->addChild(sprite);
	/////////////////////////////////////////////////////////////////////*/
	this->mapManager = new MapManager(this->spriteSheet,this, this->mWorld);

	this->runner = Runner::create(this->mWorld);
    this->spriteSheet->addChild(this->runner);

	//this->objectManager = new ObjectManager(this->spriteSheet, this->mWorld);
    //this->objectManager->initObjectOfMap(1, this->mapManager->getMapWidth());


	 scheduleUpdate();

	/////////////////////////////////
	/*
    this->mapManager = new MapManager(this, this->space);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("parkour.plist");
    this->spriteSheet = CCSpriteBatchNode::create("parkour.png");
    this->addChild(spriteSheet);
    
    this->runner = Runner::create(this->space);
    this->spriteSheet->addChild(this->runner);
    
    this->objectManager = new ObjectManager(this->spriteSheet, this->space);
    this->objectManager->initObjectOfMap(1, this->mapManager->getMapWidth());

    // must after objectManager inited
    cpSpaceAddCollisionHandler(this->space, SpriteTagrunner, SpriteTagcoin, collisionBegin, NULL
                               , NULL, NULL, this->objectManager);
    cpSpaceAddCollisionHandler(this->space, SpriteTagrunner, SpriteTagrock, collisionBegin, NULL
                               , NULL, NULL, this->objectManager);
    
    // make updater() to be called
    scheduleUpdate();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PlayLayer::notifiCoin),
                                                                  NOTIFI_MEET_COIN, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PlayLayer::notifiRock),
                                                                  NOTIFI_MEET_ROCK, NULL);
    
#if 0
    //CCPhysicsDebugNode是为了更方便debug的类，将它设置为显示之后，在场景内定义的精灵的碰撞形状块就显示出来了
    cocos2d::extension::CCPhysicsDebugNode* debugLayer = cocos2d::extension::CCPhysicsDebugNode::create(this->space);
    addChild(debugLayer, 100);
    debugLayer->setVisible(true);
#endif
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
    /*// chipmunk step
    cpSpaceStep(this->space, dt);
    
    // check and reload map
    if (true == this->mapManager->checkAndReload(this->lastEyeX)) {
        this->objectManager->removeObjectOfMap(this->mapManager->getCurMap() - 1);
        this->objectManager->initObjectOfMap(this->mapManager->getCurMap() + 1, this->mapManager->getMapWidth());
        //level up
        this->runner->levelUp();
    }
    
    this->runner->step(dt);
    // move Camera
    lastEyeX = this->runner->getPositionX() - this->runner->getoffsetPx();
    CCCamera *camera = this->getCamera();
    float eyeZ = camera->getZEye();
    camera->setEyeXYZ(lastEyeX, 0, eyeZ);
    camera->setCenterXYZ(lastEyeX, 0, 0);
    
    StatusLayer *statusLayer = (StatusLayer *)getParent()->getChildByTag(TAG_STATUSLAYER);
    statusLayer->updateMeter(lastEyeX);*/
	////////////////////////////////////////
	mWorld->Step(dt, 10, 8);
	
	if (true == this->mapManager->checkAndReload(this->lastEyeX)) {
       // this->objectManager->removeObjectOfMap(this->mapManager->getCurMap() - 1);
        //this->objectManager->initObjectOfMap(this->mapManager->getCurMap() + 1, this->mapManager->getMapWidth());
        //level up
       // this->runner->levelUp();
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