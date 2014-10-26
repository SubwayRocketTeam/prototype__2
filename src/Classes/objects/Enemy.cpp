#include "Enemy.h"

#include "common/resource.h"

using namespace cocos2d;

Enemy::Enemy(){
}
Enemy::~Enemy(){
}

Enemy *Enemy::create(){
	Enemy *e = new Enemy();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool Enemy::init(){
    if (!Unit::init(R::EnemyBody))
        return false;

    return true;
}
bool Enemy::initPhysics(){
	auto pbody = 
		PhysicsBody::createBox(body->getContentSize() - Size(0,5));
	
	pbody->setAngularVelocityLimit(0);
	pbody->setAngularDamping(1);
	pbody->setRotationEnable(true);
	
	setPhysicsBody(pbody);

	return true;
}

void Enemy::focus(){
	body->setColor(Color3B(255,0,0));
}
void Enemy::unfocus(){
	body->setColor(Color3B(255,255,255));
}