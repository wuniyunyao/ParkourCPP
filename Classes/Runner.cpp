//
//  Runner.cpp
//  PaoKu
//
//  Created by YTB on 13-11-21.
//
//

#include "Runner.h"
#include "MapManager.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"

#define RUNING_MODE "running"

Runner *Runner::create(b2World* mWorld)
{
    Runner *runner = new Runner(mWorld);
    runner->autorelease();
    return runner;
}

Runner::Runner(b2World* mWorld) : m_offsetPx(100.0)
{
    this->mWorld = mWorld;
    //this->shape = NULL;
    
    this->initWithSpriteFrameName("runner0.png");
    this->runningSize = this->getContentSize();
    
    //init crouchSize
    cocos2d::extension::CCPhysicsSprite *tmpSprite = cocos2d::extension::CCPhysicsSprite::createWithSpriteFrameName("runnerCrouch0.png");
    this->crouchSize = tmpSprite->getContentSize();
    
    initAction();
    initBody();
    initShape(RUNING_MODE);// start with running shape
    //this->setCPBody(this->body);
    
    m_stat = RunnerStatRunning;
    this->runAction(this->runningAction);
}

Runner::~Runner()
{
    this->runningAction->release();
    this->jumpUpAction->release();
    this->jumpDownAction->release();
    this->crouchAction->release();
    /*cpBodyFree(this->body);
    cpShapeFree(this->shape);*/
}

void Runner::initAction()
{
    // init runningAction
    CCArray *animFrames = CCArray::create();
    for (int i = 0; i < 8; i++)
    {
        CCString *name = CCString::createWithFormat("runner%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    this->runningAction =CCRepeatForever::create(CCAnimate::create(animation));
    this->runningAction->retain();

    // init jumpUpAction
    animFrames = CCArray::create();
    for (int i=0; i<4; i++) {
        CCString *name = CCString::createWithFormat("runnerJumpUp%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }

    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    this->jumpUpAction = CCAnimate::create(animation);
    this->jumpUpAction->retain();

    // init jumpDownAction
    animFrames->removeAllObjects();
    for (int i=0; i<2; i++) {
        CCString *name = CCString::createWithFormat("runnerJumpDown%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2);
    this->jumpDownAction = CCAnimate::create(animation);
    this->jumpDownAction->retain();

    // init crouchAction
    animFrames->removeAllObjects();
    for (int i=0; i<1; i++) {
        CCString *name = CCString::createWithFormat("runnerCrouch%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animFrames->addObject(frame);
    }
    animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
    this->crouchAction = CCAnimate::create(animation);
    this->crouchAction->retain();
}

void Runner::initBody()
{
	/////////////////////////
	//new code for Box2D by wuniyunyao
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    // 初始速度1.5
	bodyDef.fixedRotation = true;
    bodyDef.linearVelocity = b2Vec2(5, 0);
    bodyDef.position = b2Vec2(m_offsetPx /  PTM_RATIO, (MapManager::getGroundHeight() + this->runningSize.height / 2 )/  PTM_RATIO);
	bodyDef.angle = 0; //set the starting angle
	mBody = mWorld->CreateBody(&bodyDef);
    mBody->SetUserData(this);
    // 关联起来
    this->setB2Body(mBody);
	this->setPTMRatio(PTM_RATIO);
}

void Runner::levelUp()
{
    // run faster
    /*cpBodyApplyImpulse(this->body, cpv(10, 0), cpv(0, 0));*/
}

void Runner::initShape(const char* type)
{
	////////////////////////////////////////
	//b2PolygonShape shape;
	// 如果物体已经有一个形状则删掉
    if(mBody->GetFixtureList())
    {
        mBody->DestroyFixture(mBody->GetFixtureList());
    }
    if (strcmp(type,RUNING_MODE) == 0)
    {
        // 人物站立，中心改变，调整位置
        //mBody->SetTransform(b2Vec2(mBody->GetPosition().x, (MapManager::getGroundHeight() + runningSize.height / 2) / RATIO), mBody->GetAngle());
        
        // 定义runner的形状，一个box，参数是半宽高
        shape.SetAsBox(runningSize.width / 2 /  PTM_RATIO,runningSize.height / 2 /  PTM_RATIO);
        

    }else
    {
        // 由于人物下蹲的大小和站立大小不一致，所以要下调位置
        //mBody->SetTransform(b2Vec2(mBody->GetPosition().x, (MapManager::getGroundHeight()+ crouchSize.height / 2) / RATIO) ,mBody->GetAngle());
        
        // 定义runner下蹲的形状，一个box，参数是半宽高
        shape.SetAsBox(crouchSize.width / 2 /  PTM_RATIO, crouchSize.height / 2 /  PTM_RATIO);
    }
    b2FixtureDef fixDef;
    fixDef.friction = 0.0f;
    fixDef.shape = (b2Shape*)&shape;
	fixDef.density = 1;
	//fixDef.restitution = 1;
    mBody->CreateFixture(&fixDef);
	/////////////////////////////////////////
}

void Runner::jump()
{
	 if (m_stat == RunnerStatRunning/*||RunnerStatCrouch*/) {
        float impulse = mBody->GetMass() * 8;
        // 根据物体质量，施加一个向上的力，人物就会跳起
        mBody->ApplyLinearImpulse(b2Vec2(0, impulse), mBody->GetWorldCenter());
        m_stat = RunnerStatJumpUp;
        this->stopAllActions();
		//unschedule(schedule_selector(Runner::loadNormal));
        this->runAction(this->jumpUpAction);
		
		CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
        audioEngine->playEffect(JUMPMUSIC);
    }
}

void Runner::crouch()
{
    m_stat = RunnerStatCrouch;
    this->initShape("crouch");
    this->stopAllActions();
    this->runAction(this->crouchAction);
    scheduleOnce(schedule_selector(Runner::loadNormal), 1.5);
    CocosDenshion::SimpleAudioEngine *audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    audioEngine->playEffect(CROUCHMUSIC);
}

void Runner::loadNormal(float dt)
{
	initShape(RUNING_MODE);
	this->stopAllActions();
	this->runAction(runningAction);
	m_stat = RunnerStatRunning;
}

void Runner::step(float dt)
{
	 b2Vec2 vel = mBody->GetLinearVelocity();
    if (m_stat == RunnerStatJumpUp) {
        if (vel.y < 0.1) {
            m_stat = RunnerStatJumpDown;
            this->stopAllActions();
            this->runAction(this->jumpDownAction);
        }
    }
    
    if (m_stat == RunnerStatJumpDown) {
        if (vel.y == 0) {
            m_stat = RunnerStatRunning;
			this->stopAllActions();
            this->runAction(this->runningAction);
        }
    }
	//float x = mBody->GetLinearVelocity().x;
	//if(x < 5)
	mBody->SetLinearVelocity(b2Vec2(5,vel.y));
    
}