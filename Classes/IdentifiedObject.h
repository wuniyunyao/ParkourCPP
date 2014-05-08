#ifndef __STATICBLOCKOBJECT_H_
#define __STATICBLOCKOBJECT_H_
#include "cocos2d.h"
#include "Box2D\Box2D.h"
using namespace cocos2d;
/*
�ļ�����StaticBlocObject.h
�������������ڴ洢��̬�谭
�����ߣ�������ң
�������ڣ�2013/4/24
*/
class IdentifiedObject{
public:
	enum type
	{
		ST_POLYGON = 0,
		ST_CIRCLE
	};
	type shape;
	b2Fixture* fixture;
	b2Body* body;
	float32 friction;
    float32 restitution;
    float32 density;
	boolean isSensor;
	IdentifiedObject(){
		density = 1.0f;
		friction = 0;
		restitution = 0;
		fixture = NULL;
		body = NULL;
		isSensor = false;
	};
};
#endif //__STATICBLOCKOBJECT_H_