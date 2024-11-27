#include "PhysicsManager.h"

#include <box2D/box2d.h>

PhysicsManager* PhysicsManager::mSinglePhysicsManager = nullptr;

int PhysicsManager::Initialize()
{
/*
	b2Vec2 gravity(0.0f, -10.0f);

	m2DWorld = new b2World(gravity);

	// 创建地面
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = m2DWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	
	//定义一个物体对象
	b2BodyDef myBodyDef;
	//设置物体类型为动态物体
	myBodyDef.type = b2_dynamicBody;
	// 设置物体的起始位置 
	myBodyDef.position.Set(0, 20);
	//设置物体起始角度
	myBodyDef.angle = 0;

	auto dynamicBody = m2DWorld->CreateBody(&myBodyDef);

	//定义多边形对象
	b2PolygonShape boxShape;
	//设置为正方形
	boxShape.SetAsBox(1, 1);

	//定义定制器对象
	b2FixtureDef boxFixtureDef;
	//设置定制器的形状
	boxFixtureDef.shape = &boxShape;
	//设置密度
	boxFixtureDef.density = 1;
	//将定制器附加到物体上来
	dynamicBody->CreateFixture(&boxFixtureDef);

	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	for (int32 i = 0; i < 60; ++i)
	{
		m2DWorld->Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = dynamicBody->GetPosition();
		float angle = dynamicBody->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}
	*/
	return 0;
}

void PhysicsManager::Tick()
{
}

void PhysicsManager::Release()
{
	// delete m2DWorld;
	delete mSinglePhysicsManager;
}

PhysicsManager* PhysicsManager::Get()
{
	if (mSinglePhysicsManager == nullptr) {
		mSinglePhysicsManager = new PhysicsManager;
	}
	return mSinglePhysicsManager;
}
