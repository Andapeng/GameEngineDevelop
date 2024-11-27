#include "PhysicsManager.h"

#include <box2D/box2d.h>

PhysicsManager* PhysicsManager::mSinglePhysicsManager = nullptr;

int PhysicsManager::Initialize()
{
/*
	b2Vec2 gravity(0.0f, -10.0f);

	m2DWorld = new b2World(gravity);

	// ��������
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = m2DWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	
	//����һ���������
	b2BodyDef myBodyDef;
	//������������Ϊ��̬����
	myBodyDef.type = b2_dynamicBody;
	// �����������ʼλ�� 
	myBodyDef.position.Set(0, 20);
	//����������ʼ�Ƕ�
	myBodyDef.angle = 0;

	auto dynamicBody = m2DWorld->CreateBody(&myBodyDef);

	//�������ζ���
	b2PolygonShape boxShape;
	//����Ϊ������
	boxShape.SetAsBox(1, 1);

	//���嶨��������
	b2FixtureDef boxFixtureDef;
	//���ö���������״
	boxFixtureDef.shape = &boxShape;
	//�����ܶ�
	boxFixtureDef.density = 1;
	//�����������ӵ���������
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
